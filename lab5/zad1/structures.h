#ifndef ZAD1_STRUCTURES_H
#define ZAD1_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Program{
    char ** args;
} Program;

typedef struct Section{
    char* name;
    Program* programs;
} Section;

void print_section(Section *section);

#endif //ZAD1_STRUCTURES_H
