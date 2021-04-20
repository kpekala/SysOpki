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
        program->args[arg_numb] = calloc(MAX_STRING_SIZE, sizeof(char ));
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

void parse_command(char *line, Command *command){
    int itr = 0;
    int section_i = 0;
    //printf("%s",line);
    while(itr < strlen(line)){
        //printf("%d\n",section_i);
        char * section = command->sections[section_i];
        int i =0;
        while (line[itr] == ' ')
            itr++;
        while (line[itr] != ' ' && line[itr] != '\n'){
            section[i] = line[itr];
            itr++;
            i++;
        }
        while (line[itr] == ' ' || line[itr] == '\n')
            itr++;
        if (line[itr] == '|')
            itr += 2;
        section_i++;
    }
}

void parse(char* path, Section **sections, int *sections_numb, Command **commands, int *command_numb) {
    FILE * fp;
    char * line = calloc(MAX_LINE_SIZE, sizeof(char));
    fp = fopen(path, "r");
    if (fp == NULL)
        exit(1);

    int sections_i=0;
    int commands_i=0;
    while (fgets(line, MAX_LINE_SIZE, fp) != NULL) {
        if (strstr(line,"=")!= NULL){
            //printf("Section\n");
            sections[sections_i] = calloc(1, sizeof(Section));
            init_section(sections[sections_i]);
            parse_section(line,sections[sections_i]);
            sections_i++;
        }else if (strlen(line) <= 1){
            //printf("blank line\n");
        }
        else{
            //printf("pipe\n");
            commands[commands_i] = calloc(1, sizeof(Command));
            init_command(commands[commands_i]);
            parse_command(line,commands[commands_i]);
            commands_i++;
        }
    }
    fclose(fp);
    if(line)
        free(line);
    *sections_numb = sections_i;
    *command_numb = commands_i;
}
