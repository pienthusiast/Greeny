#include <stdio.h>
#include <stdlib.h>

int meh(void)
{

    char buffer[32] = {0};  /* initialized to zeroes */
    char buffer1[290];
    char buffer2[290];
    int i,j,k,m;
    FILE *fp = fopen("OWC.txt", "rb");

    if (fp == NULL) {
        perror("Failed to open file \"myfile\"");
        return EXIT_FAILURE;
    }


    for (i = 0; i <= 23; i++) {
        char rc = getc(fp);
        if (rc == EOF) {
            fputs("An error occurred while reading the file.\n", stderr);
            return EXIT_FAILURE;
        }
        buffer[i] = rc;
    }

    fclose(fp);
    for(k = 0; k <= (23); k++)
    {
	int a = buffer[k];
	itoa(a,buffer1,2);
	printf("Binary %s\n",buffer1);
	}
	for (m = 0; m <= 290; m++){
		buffer2[m] = buffer1[m];
	}
	printf("%s",buffer2);
    for(j = 0; j <= (23) ; j++){
    printf("The byte read were... %d\n", buffer[j]);
	}
    return EXIT_SUCCESS;
    
}
