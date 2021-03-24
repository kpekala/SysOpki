#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FILE_NAME_SIZE 30
#define MAX_FILE_SIZE 30000

void do_magic(char f_name1[], char f_name2[], char n1[], char n2[]);

int main() {
    do_magic("f1.txt","f2.txt","Warzone","Fornite");
    return 0;
}

void do_magic(char f_name1[], char f_name2[], char n1[], char n2[]){
    int fp1, fp2;
    fp1 = open(f_name1, O_RDONLY);
    fp2 = open(f_name2, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
    if (fp1 == -1 || fp2 == -1){
        printf("Cannot read file\n");
        return;
    }
    char * buffer1 = calloc(MAX_FILE_SIZE+1, sizeof(char));
    buffer1[MAX_FILE_SIZE] = '\0';

    size_t size1 = read(fp1,buffer1,MAX_FILE_SIZE);
    for(int i=0; i<size1; i++){
        if(&buffer1[i] != strstr(&buffer1[i],n1)){
            write(fp2,&buffer1[i],1);
        }else{
            write(fp2,n2,strlen(n2));
            i+= ((int)strlen(n1)-1);
        }
    }

    char * p_str = strstr(buffer1,n1);

    free(buffer1);
    close(fp1);
    close(fp2);
}
