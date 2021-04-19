#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "structures.h"
#include "parser.h"


int main(int ac, char** av){
    Section *section = (Section*) calloc(1, sizeof(Section));
    char line[50] = "";
    scanf("%s",line);
    parse_section(line,section);
    print_section(section);

    free(section->name);
    free(section);
    return 0;
}