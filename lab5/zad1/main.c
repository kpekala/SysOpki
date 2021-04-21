#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "structures.h"
#include "parser.h"

#define BUFFER_SIZE 100

int sections_size = 0;
int sections_numb = 0, commands_numb = 0;
Section **sections;
Command **commands;

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

void run_section(Section * section) {
    if (section->programs_numb < 1) {
        printf("Not enough programs!\n");
        return;
    }
    int pipes[2][2];

    int i;
    for (i = 0; i < section->programs_numb; i++) {
        if (i > 0) {
            close(pipes[i % 2][0]);
            close(pipes[i % 2][1]);
        }

        if (pipe(pipes[i % 2]) == -1) {
            printf("Error on pipe.\n");
            exit(EXIT_FAILURE);
        }
        pid_t cp = fork();
        if (cp == 0) {
            char **exec_params = section->programs[i]->args;

            if (i != section->programs_numb - 1) {
                close(pipes[i % 2][0]);
                if (dup2(pipes[i % 2][1], STDOUT_FILENO) < 0) {
                    exit(EXIT_FAILURE);
                }
            }
            if (i != 0) {
                close(pipes[(i + 1) % 2][1]);
                if (dup2(pipes[(i + 1) % 2][0], STDIN_FILENO) < 0) {
                    close(EXIT_FAILURE);
                }
            }
            execvp(exec_params[0], exec_params);

            exit(EXIT_SUCCESS);
        }
    }
    close(pipes[i % 2][0]);
    close(pipes[i % 2][1]);
    wait(NULL);
}

Section * find_section(char * section_name){
    for (int i=0; i<sections_numb; i++){
        if(strcmp(sections[i]->name,section_name) == 0){
            return sections[i];
        }
    }
    return NULL;
}

Section * make_section(Command * command){
    int global_i = 0;
    //int global_size = MAX_PROGRAMS * command->sections_numb;
    Section * new_section = calloc(1, sizeof(Section));
    init_section(new_section);
    for (int section_i=0; section_i<command->sections_numb; section_i++){
        Section * section = find_section(command->sections[section_i]);
        if(section == NULL){
            printf("Oops\n");
            exit(1);
        }
        new_section->programs_numb += section->programs_numb;
        for(int j=0; j<section->programs_numb; j++){
            new_section->programs[global_i] = section->programs[j];
            global_i++;
        }
    }
    return new_section;
}

void clean(){
    free_sections(sections);
    free_commands(commands);
}

int main(int argc, char** argv){
    sections = calloc(MAX_SECTIONS_SIZE, sizeof(Section));
    commands = calloc(MAX_SECTIONS_SIZE, sizeof(Command));
    parse("files/file1.txt",sections,&sections_numb,commands,&commands_numb);
    for (int i = 0; i < commands_numb; i++) {
        Command * command = commands[i];
        Section * section = make_section(command);
        if(fork() == 0){
            run_section(section);
            clean();
            free(section);
            return 0;
        }
    }
    clean();
    return 0;
}