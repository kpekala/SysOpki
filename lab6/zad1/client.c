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
void usr_handler(int);
void register_client(key_t privateKey);
void chat_loop(key_t);

int sessionID = -2;
int queue_id = -1;
int private_id = -1;
key_t  private_key;

void request_list(Message *msg);
void request_connect(Message *msg);

void init();
void print_errno();
void request_disconnect();

int main(int argc, char *argv[]) {
    init();
    char* path = getenv("HOME");
    if (path == NULL) FAILURE_EXIT("Getting $HOME failed");
    queue_id = create_queue(path, PROJECT_ID, 0, 0);

    private_id = create_queue(path, getpid(), IPC_CREAT | IPC_EXCL | 0666, 1);
    if (private_id == -1)
        FAILURE_EXIT("Creation of private queue failed");
    printf("serving key: %d\n",private_id);

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

void chat_loop(key_t receiver_key){
    printf("client: starting chat\n");
    while (1){
        Message rcv_msg;
        int ext = 0;
        while((msgrcv(private_id, &rcv_msg, MSG_SIZE, 0, IPC_NOWAIT)) != -1){
            //printf("Message of %d bytes\n",b);
            printf("Message: %s\n",rcv_msg.message_text);
            if(strcmp(rcv_msg.message_text, "quit") == 0)
                ext = 1;
        }
        if (ext){
            printf("client: closing chat\n");
            request_disconnect();
            break;
        }
        Message send_msg;
        send_msg.mtype = 1;
        if (fgets(send_msg.message_text, 50, stdin) == NULL){
            printf("client: error reading your command\n");
            continue;
        }
        if(strlen(send_msg.message_text)>=1 && send_msg.message_text[0] == '\n')
            continue;
        //printf("sending %s\n",send_msg.message_text);
        int n = strlen(send_msg.message_text);
        if (send_msg.message_text[n-1] == '\n') send_msg.message_text[n-1] = 0;
        if(msgsnd(receiver_key,&send_msg,MSG_SIZE,0) == -1)
            FAILURE_EXIT("client: sending message failed\n");

        if (strcmp(send_msg.message_text,"quit") == 0){
            request_disconnect();
            break;
        }

    }
}

void request_disconnect() {
    Message msg;
    msg.sender_pid = getpid();
    msg.mtype = DISCONNECT;
    if (msgsnd(queue_id, &msg, MSG_SIZE, 0) == -1)
        FAILURE_EXIT("client: DISCONNECT request failed");
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
    if(receiver_key == -5){
        printf("client: receiver is connected to other client!\n");
        return;
    }
    printf("receiver key: %d\n",receiver_key);

    chat_loop(receiver_key);
}



int create_queue(char *path, int ID, int flags, int save) {
    int key = ftok(path, ID);
    if(key == -1) FAILURE_EXIT("Generation of key failed");
    if(save)
        private_key = key;

    int QueueID = msgget(key, flags);
    if (QueueID == -1){
        print_errno();
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

void handle_chat(){
    printf("Handling chat\n");
    key_t sender_key;
    Message msg;

    if (msgrcv(private_id, &msg,MSG_SIZE, 0, 0) < 0)
        FAILURE_EXIT("client: receiving message failed\n");
    printf("receiver key: %s\n",msg.message_text);
    key_t  receiver_key = atoi(msg.message_text);
    chat_loop(receiver_key);
}

void usr_handler(int _) {
    handle_chat();
}

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
    if(signal(SIGUSR1, usr_handler) == SIG_ERR)
        FAILURE_EXIT("Registering USR1 failed");
}


void print_errno() {
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
        case E2BIG:
            printf("E2BIG");
            break;
        case EINTR:
            printf("EINTR");
            break;
        case EINVAL:
            printf("EINVAL");
            break;
        case ENOMSG:
            printf("ENOMSG");
            break;
    }
}

