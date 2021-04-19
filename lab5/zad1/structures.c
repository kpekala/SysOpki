
#include "structures.h"

void print_section(Section* section) {
    printf("Printing section %s: \n",section->name);
    for (int i=0; i<MAX_PROGRAMS; i++){
        print_program(section->programs[i]);
    }
}

void print_program(Program *program) {
    printf("Printing program: \n");
    for (int i=0; i<MAX_PROGRAMS; i++){
        printf("Arg %d: %s\n",i,program->args[i]);
    }
}


void init_program(Program *program) {
    program->args = (char**) calloc(MAX_ARGUMENTS, sizeof(char *));
    for (int i=0; i<MAX_ARGUMENTS; i++){
        program->args[i] = (char *) calloc(MAX_STRING_SIZE, sizeof(char ));
    }
}

void free_program(Program *program) {
    for (int i=0; i<MAX_ARGUMENTS; i++){
        free(program->args[i]);
    }
    free(program->args);
    free(program);
}

void init_section(Section *section) {
    section->name = calloc(MAX_STRING_SIZE, sizeof(char ));
    section->programs = calloc(MAX_PROGRAMS, sizeof(Program**));
    for (int i=0; i<MAX_PROGRAMS; i++){
        section->programs[i] = calloc(1, sizeof(Program));
        init_program(section->programs[i]);
    }
}

void free_section(Section *section) {
    free(section->name);
    for (int i=0; i<MAX_PROGRAMS; i++){
        free_program(section->programs[i]);
    }
    free(section->programs);
    free(section);
}

