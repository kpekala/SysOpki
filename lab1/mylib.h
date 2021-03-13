//
// Created by konrad on 11.03.2021.
//

#ifndef LAB1_MY_LIB_H
#define LAB1_MY_LIB_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAIN_ARRAY_SIZE 10
#define MAX_LINE_SIZE 256

//void import_file(char* file_name, )

int import_file(char* file_name, char** block);

void init(int arr_size);
void clean();

int rows_number(int block_index);
int merge_files(char* f_name1, char * f_name2);

int remove_block(int index);
int remove_row(int block_index, int row_index);

void print_block(int block_index);

#endif //LAB1_MY_LIB_H
