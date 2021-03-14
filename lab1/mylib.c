#include "mylib.h"

struct MainArr{
    struct Block** main_pointer;
    int array_size;
    int last_index;
} mainArr;

struct Block{
    char** pointer;
    int f_size;
};



int import_file(char* file_name, char** block){
    FILE * fp;
    char * line = calloc(MAX_LINE_SIZE, sizeof(char));
    size_t len = 0;
    ssize_t read;


    fp = fopen(file_name, "r");
    if (fp == NULL)
        exit(1);

    int i=0;
    int last_empty = 0;
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        //printf("%s\n", line);
        //printf("%lu hoho",strlen(line));
        if(line[0] != '\n'){
            strcpy(block[i],line);
        }
        else{
            strcpy(block[i]," \n");
        }
        i++;
    }
    if(last_empty == 1)
        i++;
    fclose(fp);
    if(line)
        free(line);
    return i;
}

int read_file_size(char* file_name){
    FILE * fp;
    char * line = calloc(MAX_LINE_SIZE, sizeof(char));
    size_t len = 0;
    ssize_t read;


    fp = fopen(file_name, "r");
    if (fp == NULL)
        exit(1);

    int i=0;
    int last_empty = 0;
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        if(line[0] != '\n'){
            last_empty = 0;
        }
        else{
            last_empty = 1;
        }
        i++;
    }
    if(last_empty == 1)
        i++;
    fclose(fp);
    if(line)
        free(line);
    return i;
}

void init(int arr_size){
    mainArr.main_pointer = (struct Block**) calloc(arr_size,sizeof(struct Block*));
    mainArr.array_size = arr_size;
    mainArr.last_index = -1;
    /*for(int i=0; i<array_size; i++){
        main_pointer[i] = (char **)calloc(1, sizeof(char*));
    }*/
}

void clean(){
    for(int i=0; i<mainArr.array_size; i++){
        if(mainArr.main_pointer[i] != NULL)
            free(mainArr.main_pointer[i]);
    }
    free(mainArr.main_pointer);
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

void print_block_l(char **block, int size){
    printf("\nReading block... \n");
    for(int i=0; i<size; i++){
        if(block[i] != NULL)
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
    int f_size = f_size1 + f_size2;

    //Ostatnie linijki w blokach nie posiadają symbolu \n, dodajmy je teraz
    strcat(block1[f_size1-1],"\n");
    strcat(block2[f_size2-1],"\n");

    FILE * fp;
    int i=0,i1=0,i2=0;
    fp = fopen ("temp.txt","w");
    while (i1 < f_size1 && i2 < f_size2){
        if (i % 2 == 0){
            fprintf (fp, "%s", block1[i1]);
            i1++;
        }else{
            fprintf (fp, "%s", block2[i2]);
            i2++;
        }
        i++;
    }
    while (i1 < f_size1){
        fprintf (fp, "%s", block1[i1]);
        i1++;
    }
    while (i2 < f_size2){
        fprintf (fp, "%s", block2[i2]);
        i2++;
    }
    fclose (fp);
}

int merge_files(char* f_name1, char * f_name2){
    char** block1;
    char** block2;
    char tmp_f_name[20] = "temp.txt";
    int f_size1 = read_file_size(f_name1);
    int f_size2 = read_file_size(f_name2);
    int f_size = f_size1 + f_size2;
    printf("\nRozmiar nowego pliku: %d \n",f_size);

    block1 = (char**) calloc(f_size1, sizeof(char*));
    block2 = (char**) calloc(f_size2, sizeof(char*));
    init_block(block1, f_size1);
    init_block(block2, f_size2);

    import_file(f_name1, block1);
    import_file(f_name2, block2);

    //print_block(block1,f_size1);
    //print_block(block2, f_size2);

    merge_blocks(block1, block2, f_size1, f_size2);

    //Now we create final block of merged files
    //Pointer to this block will be stored in main array
    char ** block_ptr = calloc(f_size, sizeof(char*));
    init_block(block_ptr,f_size);
    import_file(tmp_f_name,block_ptr);

    //print_block(block_ptr,f_size);

    struct Block* block = (struct Block*) calloc(1,sizeof(struct Block));
    block->pointer = block_ptr;
    block->f_size = f_size;

    mainArr.last_index++;
    mainArr.main_pointer[mainArr.last_index] = block;


    //clean_block(block_ptr,f_size);
    clean_block(block1,f_size1);
    clean_block(block2,f_size2);

    return mainArr.last_index;
}

int check_block(int index){
    if(index >= mainArr.array_size){
        printf("Out of the bound exeption!\n");
        return -1;
    }
    if(mainArr.main_pointer[index] == NULL){
        printf("There is no block with given index!\n");
        return -1;
    }
    return 0;
}

int rows_number(int block_index){
    if (check_block(block_index) == -1)
        return -1;
    return mainArr.main_pointer[block_index]->f_size;
}



int remove_block(int index){
    clean_block(mainArr.main_pointer[index]->pointer,mainArr.main_pointer[index]->f_size);
    return 0;
    /*
    if (check_block(index) == -1)
        return -1;
    for (int i=0; i<mainArr.main_pointer[index]->f_size; i++){
        printf("%d %s\n",i,mainArr.main_pointer[index]->pointer[i]);
        free(mainArr.main_pointer[index]->pointer[i]);
        free(mainArr.main_pointer[index]->pointer);
        free(mainArr.main_pointer[index]);
    }
    mainArr.main_pointer[index] = NULL;*/
}

int remove_row(int block_index, int row_index){
    struct Block* block = mainArr.main_pointer[block_index];
    if (row_index >= block->f_size && row_index < 0)
        return -1;
    free(block->pointer[row_index]);
    block->pointer[row_index] = NULL;
}

void print_block(int block_index){
    print_block_l(mainArr.main_pointer[block_index]->pointer,
                  mainArr.main_pointer[block_index]->f_size);
}