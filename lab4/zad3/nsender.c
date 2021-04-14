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

int sig1_signals_received = 0;
int signals_number = 0;
int signals_left = -1;
int mode_n =-1;
int waiting_for_last = 0;
pid_t catcher_pid;

int main(int argc, char *argv[]) {
    if(argc != 4){
        printf("Accepting only 3 arguments!\n");
        return 1;
    }

    catcher_pid = atoi(argv[1]);
    signals_number = atoi(argv[2]);
    signals_left = signals_number;
    char* mode = argv[3];

    signal(SIGUSR1, handleSIG1);
    createSIG2handler();

    kill(catcher_pid,SIGUSR1);
    signals_left--;
    //kill(catcher_pid, SIGUSR2);

    while (1){
        sleep(10);
    }

    return 0;
}


void handleSIG1(int signum){
    printf("SIGUSR1 signal received\n");
    if(waiting_for_last){
        waiting_for_last = 0;
        kill(catcher_pid, SIGUSR2);
    }
    if(signals_left > 0){
        kill(catcher_pid,SIGUSR1);
        signals_left--;
        if(signals_left == 0)
            waiting_for_last = 1;
    }else{
        sig1_signals_received++;
    }
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
