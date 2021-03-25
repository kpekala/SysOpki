#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t child_pid;
    printf("PID glownego programu: %d\n", (int)getpid());
    for(int i=0; i<5; i++){
        child_pid = fork();
        if(child_pid == 0){
            printf("Napis pochodzi z procesu z pid: %d\n",getpid());
            return 0;
        }
    }

    return 0;
}