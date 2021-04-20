#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "structures.h"
#include "parser.h"

int sections_size = 0;

void free_commands(Command **commands){
    for (int i=0; i<MAX_SECTIONS_SIZE; i++){
        if (commands[i] != NULL)
            free_command(commands[i]);
    }
    free(commands);
}

void free_sections(Section **sections){
    for (int i=0; i<MAX_SECTIONS_SIZE; i++){
        if (sections[i] != NULL)
            free_section(sections[i]);
    }
    free(sections);
}


int main(int argc, char** argv){
    Section **sections = calloc(MAX_SECTIONS_SIZE, sizeof(Section));
    Command **commands = calloc(MAX_SECTIONS_SIZE, sizeof(Command));
//    Section *section = (Section*) calloc(1, sizeof(Section));
//    init_section(section);
//    char line[50] = "skladnik = prog1 arg1 arg2 | prog2 arg3 arg4\n";
//    printf("%s",line);
//    parse_section(line,section);
//    print_section(section);
//
//    free_section(section);

    int sections_numb = 0, commands_numb = 0;
    parse("files/file1.txt",sections,&sections_numb,commands,&commands_numb);
    print_commands(commands);
    free_sections(sections);
    free_commands(commands);
    return 0;
}