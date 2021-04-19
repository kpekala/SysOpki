#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "structures.h"
#include "parser.h"

int sections_size = 0;


int main(int argc, char** argv){
    Section **sections = calloc(MAX_SECTIONS_SIZE, sizeof(Section));
    Section *section = (Section*) calloc(1, sizeof(Section));
    init_section(section);
    char line[50] = "skladnik = prog1 arg1 arg2 | prog2 arg3 arg4\n";
    printf("%s",line);
    parse_section(line,section);
    print_section(section);

    free_section(section);
    return 0;
}