#ifndef ZAD1_STRUCTURES_H
#define ZAD1_STRUCTURES_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PROGRAMS 5
#define MAX_ARGUMENTS 5
#define MAX_STRING_SIZE 30
#define MAX_SECTIONS_SIZE 10

typedef struct Program{
    char ** args;
} Program;

typedef struct Section{
    char* name;
    int programs_numb;
    Program** programs;
} Section;

typedef struct Command{
    char ** sections;
}Command;

void print_section(Section *section);
void print_program(Program *program);
void print_commands(Command ** commands);

void init_program(Program *program);
void free_program(Program *program);

void init_section(Section *section);
void free_section(Section *section);

void init_command(Command *command);
void free_command(Command *command);

#endif //ZAD1_STRUCTURES_H
