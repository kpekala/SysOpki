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
void handleSIG2(int signum);

void createSIG1handler();


int main(int argc, char *argv[]) {
    createSIG1handler();
    signal(SIGUSR2, handleSIG2);

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
        printf("Failed in creating signal handler!\n");
        exit(1);
    }
}


void handleSIG1(int signum, siginfo_t *siginfo, void *context){
    printf("SIGUSR1 signal received\n");
    if (sender_pid == -1)
        sender_pid = siginfo->si_pid;
    sig1_signals_received++;
}

void handleSIG2(int signum){
    printf("SIGUSR2 signal received\n");
    printf("Received %d SIGUSR1 signals\n", sig1_signals_received);
    printf("sender_pid: %d\n",sender_pid);
    return;
    exit(0);

    for (int i=0; i<sig1_signals_received; i++){
        kill(sender_pid,SIGUSR1);
    }
    kill(sender_pid, SIGUSR2);

    exit(0);
}
