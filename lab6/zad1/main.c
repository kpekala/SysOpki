#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <ctype.h>
#include <time.h>
#include <signal.h>

#include "communications.h"

#define FAILURE_EXIT(format, ...) { fprintf(stderr, format, ##__VA_ARGS__); exit(-1); }

void close_queue();
int create_queue(char*, int, int, int);
void int_handler(int);
void register_client(key_t privateKey);

int sessionID = -2;
int queue_id = -1;
int privateID = -1;
key_t  private_key;

int main(int argc, char *argv[]) {
    if(atexit(close_queue) == -1)
        FAILURE_EXIT("Registering client's atexit failed");
    if(signal(SIGINT, int_handler) == SIG_ERR)
        FAILURE_EXIT("Registering INT failed");

    char* path = getenv("HOME");
    if (path == NULL) FAILURE_EXIT("Getting $HOME failed");

    queue_id = create_queue(path, PROJECT_ID, 0, 0);

    privateID = create_queue(path, getpid(), IPC_CREAT | IPC_EXCL | 0666, 1);
    if (privateID == -1)
    FAILURE_EXIT("Creation of private queue failed");

    register_client(private_key);

}

int create_queue(char *path, int ID, int flags, int save) {
    int key = ftok(path, ID);
    if(key == -1) FAILURE_EXIT("Generation of key failed");
    if(save)
        private_key = key;

    int QueueID = msgget(key, flags);
    if (QueueID == -1){
        switch (errno) {
            case EACCES:
                printf("EACCES");
                break;
            case EEXIST:
                printf("EEXIST");
                break;
            case EIDRM:
                printf("EIDRM");
                break;
            case ENOENT:
                printf("ENOENT");
                break;
            case ENOSPC:
                printf("ENOSPC");
                break;
            case ENOMEM:
                printf("ENOMEM");
                break;
        }
        FAILURE_EXIT("Opening queue failed");
    }

    return QueueID;
}

void close_queue() {
    if (privateID > -1) {
        if (msgctl(privateID, IPC_RMID, NULL) == -1){
            printf("There was some error deleting clients's queue\n");
        }
        else {
            printf("Client's queue deleted successfully\n");
        }
    }
}

void int_handler(int _) { exit(2); }

void register_client(key_t privateKey) {
    Message msg;
    msg.mtype = LOGIN;
    msg.sender_pid = getpid();
    sprintf(msg.message_text, "%d", privateKey);

    if (msgsnd(queue_id, &msg, MSG_SIZE, 0) == -1)
    FAILURE_EXIT("client: LOGIN request failed\n");
    if (msgrcv(privateID, &msg, MSG_SIZE, 0, 0) == -1)
    FAILURE_EXIT("client: catching LOGIN response failed\n");
    if (sscanf(msg.message_text, "%d", &sessionID) < 1)
    FAILURE_EXIT("client: scanning LOGIN response failed\n");
    if (sessionID < 0)
    FAILURE_EXIT("client: server cannot have more clients\n");

    printf("client: client registered. Session no: %d\n", sessionID);
}

