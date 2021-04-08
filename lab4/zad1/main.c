#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void ignore();
void handle();
void mask();
void pending();
void handleSIG(int signum);

int main(int argc, char *argv[]) {
    if(argc != 2){
        printf("Accepting only one mandatory argument!\n");
        return 1;
    }
    char * option = argv[1];
    printf("%s\n",option);
    if(strcmp(option, "ignore")) {
        printf("ignore option\n");
        ignore();
    }else if (strcmp(option, "handler")){
        printf("handler option\n");
        handle();
    }else if(strcmp(option, "mask")){
        mask();
    }
    return 0;
}

void ignore(){
    signal(SIGUSR1,SIG_IGN);
}

void handleSIG(int signum){
    printf("SIGUSR1 signal received\n");
}

void handle(){
    signal(SIGUSR1, handleSIG);
}
void mask(){
    sigset_t new_mask;
    sigset_t old_mask;
    sigemptyset(&new_mask);
    sigaddset(&new_mask, SIGUSR1);
    if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
        printf("Failed in blocking signal!\n");
}
