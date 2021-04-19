#ifndef ZAD1_PARSER_H
#define ZAD1_PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "structures.h"

#define MAX_STRING_SIZE 30

void parse_section(char * line, Section* new_section);

#endif //ZAD1_PARSER_H
