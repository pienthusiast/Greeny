#include <stdio.h>
  #include <string.h>
  #define MAX 256

  int main() {
        int num;
        FILE *fp1, *fp2;
        char ch, src[MAX], tgt[MAX];

        /* get the input file name from the user */
        printf("Enter your input file name:");
        scanf("%s", src);

        /* get the output filename from the user */
        printf("Enter your output file name:");
        scanf("%s", tgt);

        /* open the source file in read mode */
        fp1 = fopen(src, "r");

        /* error handling */
        if (!fp1) {
                printf("Unable to open the input file!!\n");
                return 0;
        }

        /* open the target file in binary write mode */
        fp2 = fopen(tgt, "wb");

        /* error handling */
        if (!fp2) {
                printf("Unable to open the output file!!\n");
                return 0;
        }

        /*
         * read data from input file and write
         * the binary form of it in output file
         */
        while (!feof(fp1)) {
                /* reading one byte of data */
                fread(&ch, sizeof(char), 1, fp1);
                /* converting the character to ascii integer value */
                num = ch;
                /* writing 4 byte of data to the output file */
                fwrite(&num, sizeof(int), 1, fp2);
        }

        /* close all opened files */
        fclose(fp1);
        fclose(fp2);
        return 0;
  }
