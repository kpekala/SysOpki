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

void init();
void clean();

void merge_files(char* f_name1, char * f_name2);

#endif //LAB1_MY_LIB_H
