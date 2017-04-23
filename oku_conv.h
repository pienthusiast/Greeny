#include <stdio.h>
#include <stdlib.h>

int meh(void)
{  
  
    int i,j,k,m;
    FILE *fp = fopen("unixdict.txt", "rb");
    int fd = fileno(fp);
    struct stat buf;
    fstat(fd, &buf);
    int size = buf.st_size;
	
    char buffer[size] = {0};
    char buffer1[size];
	
	FILE *fs = fopen("Binaryswosh.bin","wb");
    if (fp == NULL) {
        perror("Failed to open file ");
        return EXIT_FAILURE;
    }

    for (i = 0; i <= (size-1); i++) {
        char rc = getc(fp);
        if (rc == EOF) {
            fputs("An error occurred while reading the file.\n", stderr);
            return EXIT_FAILURE;
        }
        buffer[i] = rc;
    }

    fclose(fp);
    
    for(k = 0; k <= (size-1); k++)
    {
	int a = buffer[k];
	itoa(a,buffer1,2);
	//printf("Binary value is...%s\n",buffer1);
	}
	fwrite(buffer1, sizeof(char),sizeof(buffer1), fs);
	
    /*for(j = 0; j <= (231534) ; j++){
    printf("Value that has been read...%x\n", buffer[j]);
	}*/
    fclose(fs);

    return EXIT_SUCCESS;
}
