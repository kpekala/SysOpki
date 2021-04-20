
#include "structures.h"

void print_section(Section* section) {
    printf("Printing section %s: \n",section->name);
    for (int i=0; i<MAX_PROGRAMS; i++){
        print_program(section->programs[i]);
    }
}

void print_command(Command * command) {
    printf("Printing command: \n");
    for (int i=0; i<MAX_PROGRAMS; i++){
        if(command->sections[i] != NULL && strlen(command->sections[i]) > 0)
            printf("%s -> ",command->sections[i]);
    }
    printf("\n");
}

void print_commands(Command ** commands){
    printf("!!!Printing commands!!!\n");
    for (int i=0; i<MAX_SECTIONS_SIZE; i++){
        if(commands[i] != NULL)
            print_command(commands[i]);
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
        //program->args[i] = (char *) calloc(MAX_STRING_SIZE, sizeof(char ));
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
    section->programs_numb = 0;
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

void init_command(Command *command) {
    command->sections = calloc(MAX_PROGRAMS, sizeof(char**));
    for (int i=0; i<MAX_PROGRAMS; i++){
        command->sections[i] = calloc(MAX_STRING_SIZE, sizeof(char ));
    }
}

void free_command(Command *command) {
    for (int i=0; i<MAX_PROGRAMS; i++){
        free(command->sections[i]);
    }
    free(command->sections);
    free(command);
}

