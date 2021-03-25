#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

#define FILE_NAME_SIZE 30
#define MAX_FILE_SIZE 256

void do_magic(char* f_name1, char* f_name2){
    int fp1, fp2;
    fp1 = open(f_name1, O_RDONLY);
    fp2 = open(f_name2, O_RDONLY);
    if (fp1 == -1 || fp2 == -1){
        printf("Cannot read file\n");
        return;
    }
    char * buffer1 = calloc(MAX_FILE_SIZE, sizeof(char));
    char * buffer2 = calloc(MAX_FILE_SIZE, sizeof(char));
    while (1){
        int a = 0,b = 0;
        while (1){
            //size_t size1 = fread(buffer1, sizeof(char), 1, fp1);
            size_t size1 = read(fp1,buffer1,1);
            if (size1 == 0 || buffer1[0] == '\n')
                break;
            a = 1;
            printf("%c",buffer1[0]);
        }
        if (a==1)
            printf("\n");
        while (1) {
            size_t size2 = read(fp2,buffer2,1);
            if (size2 == 0 || buffer2[0] == '\n')
                break;
            b = 1;
            printf("%c", buffer2[0]);
        }
        if (b==1)
            printf("\n");
        if (a==0 && b==0)
            break;

    }

    close(fp1);
    close(fp2);
    free(buffer1);
    free(buffer2);
}

int main(int argc, char ** argv) {
    char* f_name1, *f_name2;

    if(argc >= 3){
        f_name1 = argv[1];
        f_name2 = argv[2];
    }
    else{
        printf("Please enter file names\n");
        f_name1 = (char *) calloc(FILE_NAME_SIZE, sizeof(char ));
        f_name2 = (char *) calloc(FILE_NAME_SIZE, sizeof(char ));
        scanf("%s %s",f_name1,f_name2);
    }
    printf("file name 1: %s\n",f_name1);
    printf("file name 2: %s\n",f_name2);

    do_magic(f_name1,f_name2);

    if(argc < 3){
        free(f_name1);
        free(f_name2);
    }
    return 0;
}
