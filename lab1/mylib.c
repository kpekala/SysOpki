#include "mylib.h"

char ***main_pointer = NULL;

int import_file(char* file_name, char** block){
    FILE * fp;
    char * line = calloc(MAX_LINE_SIZE, sizeof(char));
    size_t len = 0;
    ssize_t read;


    fp = fopen(file_name, "r");
    if (fp == NULL)
        exit(1);

    int i=0;
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
            //printf("%s\n", line);
            //printf("%lu hoho",strlen(line));
            printf("%d ",i);
            if(block != NULL)
                strcpy(block[i],line);
        i++;
    }
    //*file_size = i;
    fclose(fp);
    if(line)
        free(line);
    return i;
}

void init(){
    main_pointer = (char***) calloc(MAIN_ARRAY_SIZE,sizeof(char**));
}

void clean(){
    free(main_pointer);
}

void clean_block(char **block, int size){
    for(int i=0; i<size; i++){
        free(block[i]);
    }
    free(block);
}

void init_block(char **block, int size){
    for(int i=0; i<size; i++){
        block[i] = (char*) calloc(MAX_LINE_SIZE, sizeof(char));
    }
}

void print_block(char **block, int size){
    printf("Reading block... \n");
    for(int i=0; i<size; i++){
        printf("%s",block[i]);
    }
    printf("\n");
}

/*
 * Opis funkcji:
 * 1. Wczytanie plików do pamieci
 * 2. Zmergowanie do pliku tymczasowego
 */

void merge_blocks(char ** block1, char** block2, int f_size1, int f_size2){

}

void merge_files(char* f_name1, char * f_name2){
    char** block1;
    char** block2;
    int f_size1 = import_file(f_name1,NULL);
    int f_size2 = import_file(f_name2,NULL);
    printf("Rozmiar nowego pliku: %d \n",f_size1 + f_size2);

    block1 = (char**) calloc(f_size1, sizeof(char*));
    block2 = (char**) calloc(f_size2, sizeof(char*));
    init_block(block1, f_size1);
    init_block(block2, f_size2);

    import_file(f_name1, block1);
    import_file(f_name2, block2);

    print_block(block1,f_size1);
    print_block(block2, f_size2);

    merge_blocks(block1, block2, f_size1, f_size2);

    clean_block(block1,f_size1);
    clean_block(block2,f_size2);
}