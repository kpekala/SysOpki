#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME_SIZE 30
#define MAX_FILE_SIZE 256

void do_magic(char f_name1[], char f_name2[], char n1[], char n2[]);

int main() {
    do_magic("f1.txt","f2.txt","Warzone","Fornite");
    return 0;
}

void do_magic(char f_name1[], char f_name2[], char n1[], char n2[]){
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

    size_t size1 = fread(buffer1, sizeof(char), f_size, fp1);
    for(int i=0; i<f_size; i++){
        if(&buffer1[i] != strstr(&buffer1[i],n1)){
            fwrite(&buffer1[i], sizeof(char ),1,fp2);
        }else{
            fwrite(n2, sizeof(char ), strlen(n2),fp2);
            i+= ((int)strlen(n1)-1);
        }
    }

    char * p_str = strstr(buffer1,n1);

    free(buffer1);
    fclose(fp1);
    fclose(fp2);
}
