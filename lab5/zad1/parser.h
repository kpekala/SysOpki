#ifndef ZAD1_PARSER_H
#define ZAD1_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"

#define MAX_STRING_SIZE 30
#define MAX_LINE_SIZE 200

void parse_section(char * line, Section* new_section);

void parse(char* path, Section **sections, int *sections_numb, Command **commands, int *command_numb);

#endif //ZAD1_PARSER_H
