#include <stdio.h>
#include <stdlib.h>
int fsize(FILE *);
int meh(void)
{
	
    char buffer[231535] = {0};  /* initialized to zeroes */
    char buffer1[231535];
  
    int i,j,k,m;
    FILE *fp = fopen("unixdict.txt", "rb");
    int size = fsize(fp);
	FILE *fs = fopen("Binaryswosh.bin","wb");
    if (fp == NULL) {
        perror("Failed to open file ");
        return EXIT_FAILURE;
    }

    for (i = 0; i <= 231534; i++) {
        char rc = getc(fp);
        if (rc == EOF) {
            fputs("An error occurred while reading the file.\n", stderr);
            return EXIT_FAILURE;
        }
        buffer[i] = rc;
    }

    fclose(fp);
    
    for(k = 0; k <= 231534; k++)
    {
	int a = buffer[k];
	itoa(a,buffer1,2);
	//printf("Binary value is...%s\n",buffer1);
	}
	fwrite(buffer1, sizeof(char),sizeof(buffer1), fs);
	
    /*for(j = 0; j <= (231534) ; j++){
    printf("Value that has been read...%x\n", buffer[j]);
	}
    fclose(fs);
    printf("%d",size);*/
    return EXIT_SUCCESS;
}
int fsize(FILE *fp){
    int prev=ftell(fp);
    fseek(fp, 0L, SEEK_END);
    int sz=ftell(fp);
    fseek(fp,prev,SEEK_SET); //go back to where we were
    return sz;
}
