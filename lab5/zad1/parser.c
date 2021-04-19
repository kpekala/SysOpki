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
        (*itr)++;
    }
    return 0;
}

int program_end_itr(char *line, int *itr){
    int size = (int)strlen(line);
    int i = *itr;
    if(line[i] == '\n')
        return i;
    while (i < size){
        if(line[i] == '|' || line[i] == '\n'){
            return i-1;
        }
        i++;
    }
    return 0;
}

void parse_program(char *line, int *itr, int parsing_end, Section* section){
    int i_pr = section->programs_numb;
    Program *program = section->programs[i_pr];
    int arg_numb = 0;
    while (*itr < parsing_end){
        parse_string(line,itr,program->args[arg_numb]);
        arg_numb++;
    }

    section->programs_numb++;
}


void parse_section(char * line, Section* new_section){
    int itr = 0;
    parse_string(line, &itr, new_section->name);
    while (is_next_program(line, &itr)){
        int parsing_end = program_end_itr(line, &itr);
        parse_program(line,&itr,parsing_end,new_section);
    }
}