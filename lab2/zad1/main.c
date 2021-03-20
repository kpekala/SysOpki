#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILE_NAME_SIZE 30
#define MAX_LINE_SIZE 256

void do_magic(char* f_name1, char* f_name2){
    FILE * fp1, *fp2;
    char * line1 = calloc(MAX_LINE_SIZE, sizeof(char));
    char * line2 = calloc(MAX_LINE_SIZE, sizeof(char));

    fp1 = fopen(f_name1, "r");
    if (fp1 == NULL)
        return;

    fp2 = fopen(f_name2, "r");
    if (fp2 == NULL)
        return;

    while (1){
        char * a1 = fgets(line1, MAX_LINE_SIZE, fp1);
        char * a2 = fgets(line2, MAX_LINE_SIZE, fp2);
        if(a1 != NULL && a2 != NULL){
            line1[strcspn(line1, "\n")] = 0;
            line2[strcspn(line2, "\n")] = 0;
            printf("%s\n",line1);
            printf("%s\n",line2);
        }else{
            if(a1 != NULL){
                line1[strcspn(line1, "\n")] = 0;
                printf("%s\n",line1);
            }
            else if(a2 != NULL){
                line2[strcspn(line2, "\n")] = 0;
                printf("%s\n",line2);
            }
            break;
        }
    }
    while (fgets(line1, MAX_LINE_SIZE, fp1) != NULL) {
        line1[strcspn(line1, "\n")] = 0;
        printf("%s\n",line1);
    }
    while (fgets(line2, MAX_LINE_SIZE, fp2) != NULL) {
        line2[strcspn(line2, "\n")] = 0;
        printf("%s\n",line2);
    }
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
