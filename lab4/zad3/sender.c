#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handleSIG1(int signum);
void handleSIG2(int signum, siginfo_t *siginfo, void *context);
void createSIG2handler();

void handleSIGRT1(int signum);
void handleSIGRT2(int signum);

int sig1_signals_received = 0;
int signals_number = 0;
int mode_n =-1;


int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("Accepting only 3 arguments!\n");
        return 1;
    }

    pid_t catcher_pid = atoi(argv[1]);
    signals_number = atoi(argv[2]);
    char* mode = argv[3];

    signal(SIGUSR1, handleSIG1);
    signal(SIGRTMIN+1, handleSIGRT1);
    signal(SIGRTMIN+2, handleSIGRT2);
    createSIG2handler();

    if (strcmp(mode, "kill") == 0){
        mode_n = 1;
        for (int i=0; i<signals_number; i++){
            kill(catcher_pid,SIGUSR1);
        }
        kill(catcher_pid, SIGUSR2);
    }else if(strcmp(mode, "SIGQUEUE") == 0){
        mode_n =2;
        union sigval value;
        value.sival_int = 2;
        for (int i=0; i<signals_number; i++){
            sigqueue(catcher_pid,SIGUSR1,value);
        }
        sigqueue(catcher_pid,SIGUSR2,value);
    }else if (strcmp(mode, "SIGRT") == 0){
        mode_n = 3;
        for (int i=0; i<signals_number; i++){
            kill(catcher_pid,SIGRTMIN + 1);
        }
        kill(catcher_pid, SIGRTMIN + 2);
    }


    while (1){
        sleep(10);
    }

    return 0;
}


void handleSIG1(int signum){
    printf("SIGUSR1 signal received\n");
    sig1_signals_received++;
}

void handleSIGRT1(int signum){
    printf("SIGRT1 signal received\n");
    sig1_signals_received++;
}

void createSIG2handler(){
    struct sigaction act;
    memset (&act, '\0', sizeof(act));
    act.sa_sigaction = (void *)handleSIG2;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;

    if (sigaction(SIGUSR2, &act, NULL) < 0) {
        printf("Failed in creating SIGUSR2 handler!\n");
        exit(1);
    }
}

void handleSIG2(int signum, siginfo_t *siginfo, void *context){
    printf("SIGUSR2 signal received\n");
    printf("Received %d SIGUSR1 signals\n", sig1_signals_received);
    printf("We should receive %d SIGUSR1 signals\n",signals_number);
    if (mode_n == 2){
        printf("Catcher was sending %d SIGUSR1 signals\n",siginfo->si_value.sival_int);
    }
    exit(0);
}

void handleSIGRT2(int signum){
    printf("SIGRT2 signal received\n");
    printf("Received %d SIGRT1 signals\n", sig1_signals_received);
    printf("We should receive %d SIGRT1 signals\n",signals_number);
    exit(0);
}