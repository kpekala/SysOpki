#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAX_LINE_SIZE 256
#define MAX_FILE_SIZE 3000000

void do_magic(char* f_name1, char* f_name2){
    int fp1, fp2;
    fp1 = open(f_name1, O_RDONLY);
    fp2 = open(f_name2, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0644);
    if (fp1 == -1 || fp2 == -1){
        printf("Cannot read file\n");
        return;
    }

    char * buffer1 = calloc(MAX_FILE_SIZE, sizeof(char));

    size_t size1 = read(fp1,buffer1,MAX_FILE_SIZE);

    int line_chars_count = 0;
    for(int i=0; i<size1; i++){
        line_chars_count++;
        if(buffer1[i] == '\n'){
            write(fp2,"\n",1);
            line_chars_count = 0;
        }
        else if (line_chars_count <=50)
            write(fp2,&buffer1[i],1);
        else{
            line_chars_count = 1;
            write(fp2,"\n",1);
            write(fp2,&buffer1[i],1);
        }
    }

    free(buffer1);
    close(fp1);
    close(fp2);
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