#include "parser.h"


void parse_string(const char * line, int *itr, char*name){
    int i = *itr;
    int i_n = 0;
    while (line[i] != ' ' && line[i] != '\n' && line[i] != '\0'){
        name[i_n] = line[i];
        i++;
        i_n++;
    }
    while (line[i] == ' ')
        i++;
    *itr = i;
}

int is_next_program(char *line, int *itr){
    int size = (int)strlen(line);
    if(line[*itr] == '\n')
        return 0;
    while (*itr < size){
        if(line[*itr] == '=' || line[*itr] == '|'){
            *itr += 2;
            return 1;
        }
        itr++;
    }
    return 0;
}


void parse_section(char * line, Section* new_section){
    // is id necessary?
    int itr = 0;
    new_section->name = calloc(MAX_STRING_SIZE, sizeof(char));
    parse_string(line, &itr, new_section->name);
    printf("i=%d\n",itr);
    while (is_next_program(line, &itr)){
        //parsing program
    }
}