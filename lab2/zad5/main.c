#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINE_SIZE 256

void do_magic(char* f_name1, char* f_name2){
    FILE * fp1, *fp2;
    fp1 = fopen(f_name1, "r");
    fp2 = fopen(f_name2, "w");
    if (fp1 == NULL || fp2 == NULL){
        printf("Cannot read file\n");
        return;
    }

    fseek (fp1 , 0 , SEEK_END);
    long f_size = ftell (fp1);
    printf("size %ld\n",f_size);
    rewind(fp1);
    char * buffer1 = calloc(f_size, sizeof(char));
    fread(buffer1, sizeof(char), f_size, fp1);

    int line_chars_count = 0;
    for(int i=0; i<f_size; i++){
        line_chars_count++;
        if(buffer1[i] == '\n'){
            fwrite("\n", sizeof(char ),1,fp2);
            line_chars_count = 0;
        }
        else if (line_chars_count <=50)
            fwrite(&buffer1[i], sizeof(char ),1,fp2);
        else{
            line_chars_count = 1;
            fwrite("\n", sizeof(char ),1,fp2);
            fwrite(&buffer1[i], sizeof(char ),1,fp2);
        }
    }

    free(buffer1);
    fclose(fp1);
    fclose(fp2);
}


int main(int argc, char ** argv) {
    char* f_name1, *f_name2;

    if(argc >= 3){
        f_name1 = argv[1];
        f_name2 = argv[2];
    }
    else{
        printf("Not enough arguments\n");
        return 1;
    }

    do_magic(f_name1,f_name2);

    return 0;
}