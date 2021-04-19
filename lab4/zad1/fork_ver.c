#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void ignore();
void handle();
void mask();
void unmask();
void pending();
void handleSIG(int signum);
void print_parent();

int is_parent = 1;
int child_raise = 1;
sigset_t new_mask;

int main(int argc, char *argv[]) {
    if(argc != 2){
        printf("Accepting only one mandatory argument!\n");
        return 1;
    }
    char * option = argv[1];
    handle();
    if(strcmp(option, "ignore") == 0) {
        printf("ignore option\n");
        ignore();
    }else if (strcmp(option, "handler") == 0){
        printf("handler option\n");
    }else if(strcmp(option, "mask") == 0){
        printf("mask option\n");
        mask();
    }else if (strcmp(option, "pending") == 0){
        printf("pending option\n");
        mask();
        child_raise = 0;
    }

    raise(SIGUSR1);
    pid_t child_pid = fork();
    if (child_pid == 0){
        is_parent = 0;
        if(child_raise)
            raise(SIGUSR1);
    }
    if (!child_raise)
        unmask();

    return 0;
}

void ignore(){
    signal(SIGUSR1,SIG_IGN);
}

void handleSIG(int signum){
    printf("SIGUSR1 signal received, is_parent: %d\n",is_parent);
    if(!child_raise){
        printf("signal unblocked\n");
    }
}

void handle(){
    signal(SIGUSR1, handleSIG);
}
void pending(){

}

void mask(){
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGUSR1);
    if (sigprocmask(SIG_BLOCK, &new_mask, NULL) < 0)
        printf("Failed in blocking signal!\n");
}

void unmask(){
    sigdelset(&new_mask, SIGUSR1);
    if (sigprocmask(SIG_SETMASK, &new_mask, NULL) < 0)
        printf("Failed in unblocking signal!\n");
}

void print_parent(){

}
