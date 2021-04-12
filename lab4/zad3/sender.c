#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int sig1_signals_received = 0;


void handleSIG1(int signum);
void handleSIG2(int signum);


int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("Accepting only 3 arguments!\n");
        return 1;
    }

    pid_t catcher_pid = atoi(argv[1]);
    int signals_number = atoi(argv[2]);
    int mode = atoi(argv[3]);

    signal(SIGUSR1, handleSIG1);
    signal(SIGUSR2, handleSIG2);

    for (int i=0; i<signals_number; i++){
        kill(catcher_pid,SIGUSR1);
    }
    kill(catcher_pid, SIGUSR2);

    return 0;
}


void handleSIG1(int signum){
    printf("SIGUSR1 signal received\n");
    sig1_signals_received++;
}

void handleSIG2(int signum){
    printf("SIGUSR2 signal received\n");
    printf("Received %d SIGUSR1 signals\n", sig1_signals_received);
    exit(0);
}