#define _GNU_SOURCE

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
void int_handler(int);
void do_init(struct Message *msg);

int queue_descriptor = -2;
int active = 1;
int clients_data[MAX_CLIENTS][2];
int client_count = 0;


int main() {
    if (atexit(close_queue) == -1)
    FAILURE_EXIT("server: registering server's atexit failed\n");

    if (signal(SIGINT, int_handler) == SIG_ERR)
        FAILURE_EXIT("server: registering INT failed\n");

    struct msqid_ds current_state;

    char* path = getenv("HOME");
    if(path == NULL)
        FAILURE_EXIT("server: getting environmental variable 'HOME' failed\n");

    key_t publicKey = ftok(path, PROJECT_ID);
    if(publicKey == -1)
        FAILURE_EXIT("server: generation of publicKey failed\n");

    queue_descriptor = msgget(publicKey, IPC_CREAT | IPC_EXCL | 0666);
    if(queue_descriptor == -1)
        FAILURE_EXIT("server: creation of public queue failed\n");

    Message buffer;
    while(1) {
        if (active == 0) {
            if (msgctl(queue_descriptor, IPC_STAT, &current_state) == -1)
                FAILURE_EXIT("server: getting current state of public queue failed\n");
            if (current_state.msg_qnum == 0) break;
        }

        if (msgrcv(queue_descriptor, &buffer, MSG_SIZE, 0, 0) < 0)
            FAILURE_EXIT("server: receiving message failed\n");
        handle_public_queue(&buffer);
    }
    return 0;
}

void handle_public_queue(Message *msg) {
    if (msg == NULL) return;
    switch(msg->mtype){
        case INIT:
            do_init(msg);
            break;
        default:
            break;
    }
}
void close_queue() {
    if (queue_descriptor > -1) {
        int tmp = msgctl(queue_descriptor, IPC_RMID, NULL);
        if (tmp == -1) {
            printf("server: there was some error deleting server's queue\n");
        }
        printf("server: queue deleted successfully\n");
    }
}

void do_init(struct Message *msg) {
    key_t client_queue_key;
    if (sscanf(msg->message_text, "%d", &client_queue_key) < 0)
        FAILURE_EXIT("server: reading client_queue_key failed\n");

    int client_queue_id = msgget(client_queue_key, 0);
    if (client_queue_id == -1)
    FAILURE_EXIT("server: reading client_queue_id failed\n");

    int client_pid = msg->sender_pid;
    msg->mtype = INIT;
    msg->sender_pid = getpid();

    if (client_count > MAX_CLIENTS - 1) {
        printf("server: maximum number of clients reached\n");
        sprintf(msg->message_text, "%d", -1);
    } else {
        clients_data[client_count][0] = client_pid;
        clients_data[client_count++][1] = client_queue_id;
        sprintf(msg->message_text, "%d", client_count - 1);
    }

    if (msgsnd(client_queue_id, msg, MSG_SIZE, 0) == -1)
    FAILURE_EXIT("server: LOGIN response failed\n");
}


void int_handler(int _) { exit(2); }