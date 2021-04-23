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

#define FAILURE_EXIT(format, ...) { printf(format); exit(-1); }

void close_queue();
int create_queue(char*, int, int, int);
void int_handler(int);
void register_client(key_t privateKey);

int sessionID = -2;
int queue_id = -1;
int private_id = -1;
key_t  private_key;

void request_list(Message *msg);
void request_connect(Message *msg);

void init();


int main(int argc, char *argv[]) {
    init();
    char* path = getenv("HOME");
    if (path == NULL) FAILURE_EXIT("Getting $HOME failed");
    queue_id = create_queue(path, PROJECT_ID, 0, 0);

    private_id = create_queue(path, getpid(), IPC_CREAT | IPC_EXCL | 0666, 1);
    if (private_id == -1)
        FAILURE_EXIT("Creation of private queue failed");

    register_client(private_key);
    char cmd[20];
    Message msg;
    while(1) {
        msg.sender_pid = getpid();
        printf("client: enter your request: ");
        if (fgets(cmd, 20, stdin) == NULL){
            printf("client: error reading your command\n");
            continue;
        }
        int n = strlen(cmd);
        if (cmd[n-1] == '\n') cmd[n-1] = 0;


        if (strcmp(cmd, "list") == 0) {
            request_list(&msg);
        }else if (strcmp(cmd, "connect") == 0) {
            request_connect(&msg);
        }else if (strcmp(cmd, "quit") == 0) {
            exit(0);
        } else {
            printf("client: incorrect command\n");
        }
    }
}

void request_list(Message *msg) {
    msg->mtype = LIST;
    if (msgsnd(queue_id, msg, MSG_SIZE, 0) == -1)
    FAILURE_EXIT("client: LIST request failed");
    if (msgrcv(private_id, msg, MSG_SIZE, 0, 0) == -1)
    FAILURE_EXIT("client: catching LIST response failed");
    printf("%s", msg->message_text);
}

void request_connect(Message *msg) {
    msg->mtype = CONNECT;
    int receiver_id;
    scanf("%d",&receiver_id);
    sprintf(msg->message_text, "%d",receiver_id);
    printf("client: sending receiver id: %s\n",msg->message_text);
    if (msgsnd(queue_id, msg, MSG_SIZE, 0) == -1)
        FAILURE_EXIT("client: CONNECT request failed");
    if (msgrcv(private_id, msg, MSG_SIZE, 0, 0) == -1)
        FAILURE_EXIT("client: catching CONNECT response failed");
    key_t receiver_key;
    receiver_key = atoi(msg->message_text);
    printf("receiver key: %d\n",receiver_key);

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
    if (private_id > -1) {
        if (msgctl(private_id, IPC_RMID, NULL) == -1){
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
    msg.mtype = INIT;
    msg.sender_pid = getpid();
    sprintf(msg.message_text, "%d", privateKey);

    printf("elo\n");
    if (msgsnd(queue_id, &msg, MSG_SIZE, 0) == -1)
        FAILURE_EXIT("client: LOGIN request failed\n");
    if (msgrcv(private_id, &msg, MSG_SIZE, 0, 0) == -1)
        FAILURE_EXIT("client: catching LOGIN response failed\n");
    if (sscanf(msg.message_text, "%d", &sessionID) < 1)
        FAILURE_EXIT("client: scanning LOGIN response failed\n");
    if (sessionID < 0)
        FAILURE_EXIT("client: server cannot have more clients\n");

    printf("client: client registered. Session no: %d\n", sessionID);
}

void init(){
    setvbuf (stdout, NULL, _IONBF, 0);
    if(atexit(close_queue) == -1)
    FAILURE_EXIT("Registering client's atexit failed");
    if(signal(SIGINT, int_handler) == SIG_ERR)
    FAILURE_EXIT("Registering INT failed");
}

