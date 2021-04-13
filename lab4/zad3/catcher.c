#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int sig1_signals_received = 0;
pid_t sender_pid = -1;

void handleSIG1(int signum, siginfo_t *siginfo, void *context);
void handleSIG2(int signum, siginfo_t *siginfo, void *context);
void handleSIGRT1(int signum);
void handleSIGRT2(int signum, siginfo_t *siginfo, void *context);
void createSIG1handler();
void createSIG2handler();
void createSIGRT2handler();


int main(int argc, char *argv[]) {
    createSIG1handler();
    createSIG2handler();

    signal(SIGRTMIN + 1,handleSIGRT1);
    createSIGRT2handler();

    printf("Catcher pid: %d\n",getpid());

    while (1){
        sleep(10);
    }
    return 0;
}

void createSIG1handler(){
    struct sigaction act;
    memset (&act, '\0', sizeof(act));
    act.sa_sigaction = (void *)handleSIG1;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;

    if (sigaction(SIGUSR1, &act, NULL) < 0) {
        printf("Failed in creating SIGUSR1 handler!\n");
        exit(1);
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

void createSIGRT2handler(){
    struct sigaction act;
    memset (&act, '\0', sizeof(act));
    act.sa_sigaction = (void *)handleSIGRT2;
    sigemptyset(&act.sa_mask);
    act.sa_flags = SA_SIGINFO;

    if (sigaction(SIGRTMIN + 2, &act, NULL) < 0) {
        printf("Failed in creating SIGUSR2 handler!\n");
        exit(1);
    }
}

void handleSIG1(int signum, siginfo_t *siginfo, void *context){
    printf("SIGUSR1 signal received\n");
    if (sender_pid == -1)
        sender_pid = siginfo->si_pid;
    sig1_signals_received++;
}

void handleSIG2(int signum, siginfo_t *siginfo, void *context){
    printf("SIGUSR2 signal received\n");
    printf("Received %d SIGUSR1 signals\n", sig1_signals_received);
    if (sender_pid == -1)
        sender_pid = siginfo->si_pid;


    for (int i=0; i<sig1_signals_received; i++){
        kill(sender_pid,SIGUSR1);
    }
    if (siginfo->si_value.sival_int == 2){
        union sigval value;
        value.sival_int = sig1_signals_received;
        sigqueue(sender_pid,SIGUSR2,value);
    }
    else{
        kill(sender_pid, SIGUSR2);
    }

    exit(0);
}

void handleSIGRT1(int signum){
    printf("SIGRT1 signal received\n");
    sig1_signals_received++;
}

void handleSIGRT2(int signum, siginfo_t *siginfo, void *context){
    printf("SIGRT2 signal received\n");
    printf("Received %d SIGRT1 signals\n", sig1_signals_received);
    if (sender_pid == -1)
        sender_pid = siginfo->si_pid;

    for (int i=0; i<sig1_signals_received; i++){
        kill(sender_pid,SIGRTMIN + 1);
    }
    kill(sender_pid, SIGRTMIN+2);
    exit(0);
}
