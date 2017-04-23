#include <stdio.h>
  #include <string.h>
  #define MAX 256

  int main() {
        int num;
        FILE *fp1, *fp2;
        char ch, src[MAX], tgt[MAX];

        printf("Enter your input file name:");
        scanf("%s", src);

        printf("Enter your output file name:");
        scanf("%s", tgt);
        
        fp1 = fopen(src, "r");
    
        if (!fp1) {
                printf("Unable to open the input file!!\n");
                return 0;
        }

        fp2 = fopen(tgt, "wb");
        
        if (!fp2) {
                printf("Unable to open the output file!!\n");
                return 0;
        }

        while (!feof(fp1)) {
                
                fread(&ch, sizeof(char), 1, fp1);
                
                num = ch;
                
                fwrite(&num, sizeof(int), 1, fp2);
        }

        
        fclose(fp1);
        fclose(fp2);
        return 0;
  }
