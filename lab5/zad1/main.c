#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include "structures.h"
#include "parser.h"

#define BUFFER_SIZE 100

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

void run_section(Section * section){
    if (section->programs_numb < 2){
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

        if(pipe(pipes[i % 2]) == -1) {
            printf("Error on pipe.\n");
            exit(EXIT_FAILURE);
        }
        pid_t cp = fork();
        if (cp == 0) {
            char ** exec_params = section->programs[i]->args;

            if ( i  !=  section->programs_numb - 1) {
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
    exit(0);
    /*char * buffer = calloc(BUFFER_SIZE, sizeof(char ));
    //int old_fd[2];
    int new_fd[2];
    pipe(new_fd);
    //pipe(old_fd);
    for (int i=0; i<section->programs_numb; i++){
        //printf("haha %d\n",i);
        pid_t c_pid = fork();
        if(c_pid == 0){
            printf("haha %d\n",i);
            //creating next process
            Program *program = section->programs[i];
            if (i==0){
                dup2(new_fd[1],STDOUT_FILENO);
                printf("%d, args: %s %s\n",i, program->args[0], program->args[1]);
                execv(program->args[0],program->args);
                return;
                //printf("%d\n",ix);
                printf("elo\n");
            }else{
                printf("xdd %d\n",i);
                if(fork() == 0){
                    dup2(new_fd[1],STDOUT_FILENO);
                    dup2(new_fd[0],STDIN_FILENO);
                    printf("argsx: %s %s\n",program->args[0], program->args[1]);
                    execv(program->args[0],program->args);
                    return;
                    printf("elo2\n");
                }else{
                    write(new_fd[1],buffer, sizeof(buffer));
                    free(buffer);
                    return;
                }
                return;
            }
        }else{
            //reading process output
            close(new_fd[1]);
            read(new_fd[0],buffer,BUFFER_SIZE);
            printf("%s buffer\n",buffer);
        }
    }
    free(buffer);*/

}

int main(int argc, char** argv){
    Section **sections = calloc(MAX_SECTIONS_SIZE, sizeof(Section));
    Command **commands = calloc(MAX_SECTIONS_SIZE, sizeof(Command));

    int sections_numb = 0, commands_numb = 0;
    parse("files/file1.txt",sections,&sections_numb,commands,&commands_numb);
    run_section(sections[0]);
    //print_commands(commands);
    free_sections(sections);
    free_commands(commands);
    return 0;
}