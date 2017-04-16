#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
 
void* mem_alloc(size_t item_size, size_t n_item)
{
  size_t *x = calloc(1, sizeof(size_t)*2 + n_item * item_size);
  x[0] = item_size;
  x[1] = n_item;
  return x + 2;
}
 
void* mem_extend(void *m, size_t new_n)
{
  size_t *x = (size_t*)m - 2;
  x = realloc(x, sizeof(size_t) * 2 + *x * new_n);
  if (new_n > x[1])
    memset((char*)(x + 2) + x[0] * x[1], 0, x[0] * (new_n - x[1]));
  x[1] = new_n;
  return x + 2;
}
 
inline void _clear(void *m)
{
  size_t *x = (size_t*)m - 2;
  memset(m, 0, x[0] * x[1]);
}
 
#define _new(type, n) mem_alloc(sizeof(type), n)
#define _del(m)   { free((size_t*)(m) - 2); m = 0; }
#define _len(m)   *((size_t*)m - 1)
#define _setsize(m, n)  m = mem_extend(m, n)
#define _extend(m)  m = mem_extend(m, _len(m) * 2)
 
typedef uint8_t byte;
typedef uint16_t ushort;
 
#define M_CLR 256 
#define M_EOD 257 
#define M_NEW 258 
 
typedef struct {
  ushort next[256];
} lzw_enc_t;
 

typedef struct {
  ushort prev, back;
  byte c;
} lzw_dec_t;
 
byte* lzw_encode(byte *in, int max_bits)
{
  int len = _len(in), bits = 9, next_shift = 512;
  ushort code, c, nc, next_code = M_NEW;
  lzw_enc_t *d = _new(lzw_enc_t, 512);
 
  if (max_bits > 15) max_bits = 15;
  if (max_bits < 9 ) max_bits = 12;
 
  byte *out = _new(ushort, 4);
  int out_len = 0, o_bits = 0;
  uint32_t tmp = 0;
 
  inline void write_bits(ushort x) {
    tmp = (tmp << bits) | x;
    o_bits += bits;
    if (_len(out) <= out_len) _extend(out);
    while (o_bits >= 8) {
      o_bits -= 8;
      out[out_len++] = tmp >> o_bits;
      tmp &= (1 << o_bits) - 1;
    }
  }
 
 
  for (code = *(in++); --len; ) {
    c = *(in++);
    if ((nc = d[code].next[c]))
      code = nc;
    else {
      write_bits(code);
      nc = d[code].next[c] = next_code++;
      code = c;
    }
 
   
    if (next_code == next_shift) {
      if (++bits > max_bits) {
        write_bits(M_CLR);
 
        bits = 9;
        next_shift = 512;
        next_code = M_NEW;
        _clear(d);
      } else 
        _setsize(d, next_shift *= 2);
    }
  }
 
  write_bits(code);
  write_bits(M_EOD);
  if (tmp) write_bits(tmp);
 
  _del(d);
 
  _setsize(out, out_len);
  return out;
}
 
byte* lzw_decode(byte *in)
{
  byte *out = _new(byte, 4);
  int out_len = 0;
 
  inline void write_out(byte c)
  {
    while (out_len >= _len(out)) _extend(out);
    out[out_len++] = c;
  }
 
  lzw_dec_t *d = _new(lzw_dec_t, 512);
  int len, j, next_shift = 512, bits = 9, n_bits = 0;
  ushort code, c, t, next_code = M_NEW;
 
  uint32_t tmp = 0;
  inline void get_code() {
    while(n_bits < bits) {
      if (len > 0) {
        len --;
        tmp = (tmp << 8) | *(in++);
        n_bits += 8;
      } else {
        tmp = tmp << (bits - n_bits);
        n_bits = bits;
      }
    }
    n_bits -= bits;
    code = tmp >> n_bits;
    tmp &= (1 << n_bits) - 1;
  }
 
  inline void clear_table() {
    _clear(d);
    for (j = 0; j < 256; j++) d[j].c = j;
    next_code = M_NEW;
    next_shift = 512;
    bits = 9;
  };
 
  clear_table(); 
  for (len = _len(in); len;) {
    get_code();
    if (code == M_EOD) break;
    if (code == M_CLR) {
      clear_table();
      continue;
    }
 
    if (code >= next_code) {
      fprintf(stderr, "Bad sequence\n");
      _del(out);
      goto bail;
    }
 
    d[next_code].prev = c = code;
    while (c > 255) {
      t = d[c].prev; d[t].back = c; c = t;
    }
 
    d[next_code - 1].c = c;
 
    while (d[c].back) {
      write_out(d[c].c);
      t = d[c].back; d[c].back = 0; c = t;
    }
    write_out(d[c].c);
 
    if (++next_code >= next_shift) {
      if (++bits > 16) {
        fprintf(stderr, "There are too many bits\n");
        _del(out);
        goto bail;
      }
      _setsize(d, next_shift *= 2);
    }
  }
 
  if (code != M_EOD) fputs("Bits did not end in end of the data \n", stderr);
 
  _setsize(out, out_len);
bail: _del(d);
  return out;
}
 
int main()
{
  int i, fd = open("unixdict.txt", O_RDONLY);
 
  if (fd == -1) {
    fprintf(stderr, "Can't read the file\n");
    return 1;
  };
 
  struct stat st;
  fstat(fd, &st);
 
  byte *in = _new(char, st.st_size);
  read(fd, in, st.st_size);
  _setsize(in, st.st_size);
  close(fd);
 
  printf("Input size of the file:   %d\n", _len(in));
 
  byte *enc = lzw_encode(in, 9);
  printf("Encoded size of the file: %d\n", _len(enc));
 
  byte *dec = lzw_decode(enc);
  printf("Decoded size of the file: %d\n", _len(dec));
 
  for (i = 0; i < _len(dec); i++)
    if (dec[i] != in[i]) {
      printf("Bad decoding process at %d\n", i);
      break;
    }
 
  if (i == _len(dec)) printf("Correctly decoded as can be seen from Input size and the Decoded size heheh (kips ;))\n");
 
 
  _del(in);
  _del(enc);
  _del(dec);
 
  return 0;
}
