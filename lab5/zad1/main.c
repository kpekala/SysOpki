#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "structures.h"
#include "parser.h"


int main(int ac, char** av){
    Section *section = (Section*) calloc(1, sizeof(Section));
    init_section(section);
    char line[50] = "skladnik = prog1 arg1 arg2 | prog2 arg3 arg4\n";
    printf("%s",line);
    parse_section(line,section);
    print_section(section);

    free_section(section);
    return 0;
}