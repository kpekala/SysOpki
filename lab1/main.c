#include <stdio.h>
#include <stdlib.h>

#include "mylib.h"

#define STRING_SIZE 10
#define BLOCK_SIZE 10


void free_block(char** block_pointer){
    for(int i=0; i<BLOCK_SIZE; i++){
        free(block_pointer[i]);
    }
    free(block_pointer);
}
/*void init_block(char** block_pointer){
    for(int i=0; i<BLOCK_SIZE; i++){
        block_pointer[i] = (char*) calloc(STRING_SIZE, sizeof(char));
    }
}*/
int main() {
    /*char** block_pointer;
    block_pointer = (char**)calloc(BLOCK_SIZE, sizeof(char*));
    init_block(block_pointer);

    int *lines_numb = malloc(sizeof(int));
    import_file("file1.txt",block_pointer, lines_numb);

    for(int i=0; i<*lines_numb; i++){
        printf("%s", block_pointer[i]);
    }

    free(lines_numb);
    free_block(block_pointer);*/

    char f_name1[20] = "file1.txt";
    char f_name2[20] = "file2.txt";
    init();
    merge_files(f_name1,f_name2);
    clean();
    return 0;
}
