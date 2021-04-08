#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
int main(int argc, char *argv[]) {
    if(argc != 2){
        printf("Number of arguments needs to be exactly 1\n");
        return 1;
    }
    int n = atoi(argv[1]);
    pid_t child_pid;
    printf("PID glownego programu: %d\n", (int)getpid());
    for(int i=0; i<n; i++){
        child_pid = fork();
        if(child_pid == 0){
            printf("Napis pochodzi z procesu z pid: %d\n",getpid());
            return 0;
        }
    }

    return 0;
}