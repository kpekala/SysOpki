#include "mylib.h"



void import_file(char* file_name, char** block, int *file_size){
    FILE * fp;
    char * line = calloc(256, sizeof(char));
    size_t len = 0;
    ssize_t read;

    fp = fopen(file_name, "r");
    if (fp == NULL)
        exit(1);

    int i=0;
    while (fgets(line, 256, fp) != NULL) {

            //printf("%s\n", line);
            //printf("%lu hoho",strlen(line));
            strcpy(block[i],line);

        i++;
    }
    *file_size = i;
    fclose(fp);
}