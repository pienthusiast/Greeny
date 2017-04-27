#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <malloc.h>

//#define PAGE_SIZE 1024

//char *getNextLine(FILE *, size_t *);
int fsize(FILE *);
int meh(void)
{
  
    int i,j,k,m;
    FILE *fp = fopen("unixdict.txt", "rb");
    
	/*int fd = fileno(fp);
	struct stat buf;
	fstat(fd, &buf);
	int size = buf.st_size;*/
	int size = fsize(fp);
	
    char buffer[size];
    char buffer1[size];
    
	FILE *fs = fopen("binaryswosh.bin","wb");
    if (fp == NULL) {
        perror("Failed to open file ");
        return EXIT_FAILURE;
    }
	//fread(buffer,8,size,fp);
    for (i = 0; i <= (size-1); i++) {
        char rc = getc(fp);
        if (rc == EOF) {
            fputs("An error occurred while reading the file.\n", stderr);
            return EXIT_FAILURE;
        }
        buffer[i] = rc;
    }
    fclose(fp);
    
    for(k = (size-1); k >= 0; k--)
    {
	int a = buffer[k];
	m = a>>k;
	if (m&1)
		buffer1[k] = 1;
	else
		buffer1[k] = 0;

	printf("%d",buffer1[k]);
	//itoa(a,buffer1,2);
	
	//printf("Binary value is...%s\n",buffer1);
	}
	fwrite(buffer1,sizeof(char),sizeof(buffer1), fs);
	//printf("%s",buffer1);
    /*for(j = 0; j <= (231534) ; j++){
    printf("Value that has been read...%x\n", buffer[j]);
	}*/
    //fclose(fs);
    return EXIT_SUCCESS;
}
int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}
/*char *getNextLine(FILE *stream, size_t *bufferSize)
 {
   char input[PAGE_SIZE];  // allocate 
   int done = 0;
   char *targetBuffer = NULL;
   *bufferSize = 0;

   while (!done)
   {
     if(fgets(input, sizeof input, stream) != NULL)
     {
       char *tmp;
       char *newline = strchr(input, '\n');
       if (newline != NULL)
       {
         done = 1;
         *newline = 0;
       }
       tmp = (char*)realloc(targetBuffer, sizeof (*tmp * (*bufferSize + strlen(input))));
       if (tmp)
       {
         targetBuffer = tmp;
         *bufferSize += strlen(input);
         strcat(targetBuffer, input);
       }
       else
       {
         free(targetBuffer);
         targetBuffer = NULL;
         *bufferSize = 0;
         fprintf(stderr, "Unable to allocate or extend input buffer\n");

       }
     }
   }
}*/
