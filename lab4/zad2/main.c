#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/times.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

void handleSIG(int signum, siginfo_t *siginfo, void *context);
void handleSIG2(int signum, siginfo_t *siginfo, void *context);
void handleSIG3(int signum, siginfo_t *siginfo, void *context);
void createSIGhandler(int flags, int signal, void* handler);

int main(int argc, char *argv[]) {
    createSIGhandler(SA_SIGINFO, SIGUSR1, (void *)handleSIG);
    createSIGhandler(SA_SIGINFO | SA_RESTART, SIGTSTP, (void *)handleSIG2);
    createSIGhandler(SA_SIGINFO | SA_RESETHAND, SIGUSR2, (void *)handleSIG3);
    int t;
    scanf("%d", &t);

    raise(SIGUSR1);
    raise(SIGUSR2);
    raise(SIGUSR2);
    return 0;
}

void createSIGhandler(int flags, int signal, void* handler){
    struct sigaction act;
    memset (&act, '\0', sizeof(act));
    act.sa_sigaction = handler;
    sigemptyset(&act.sa_mask);
    act.sa_flags = flags;

    if (sigaction(signal, &act, NULL) < 0) {
        printf("Failed in creating SIGUSR handler!\n");
        exit(1);
    }
}

void handleSIG(int signum, siginfo_t *siginfo, void *context){
    printf("Received signal: %d from program: %d\n",signum,siginfo->si_pid);
}


void handleSIG2(int signum, siginfo_t *siginfo, void *context){
    printf("Received signal: %d from program: %d\n",signum,siginfo->si_pid);
}

void handleSIG3(int signum, siginfo_t *siginfo, void *context){
    printf("Received signal: %d from program: %d\n",signum,siginfo->si_pid);
}
