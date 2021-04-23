#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#define MAX_CLIENTS  10
#define PROJECT_ID 0x099
#define MAX_CONT_SIZE 4096
#define MAX_STRING_SIZE 60

typedef enum mtype {
    LIST = 1, INIT = 2, CONNECT = 3, DISCONNECT = 4
} mtype;

typedef struct Message {
    long mtype;
    pid_t sender_pid;
    char message_text[MAX_CONT_SIZE];
} Message;

const size_t MSG_SIZE = sizeof(Message) - sizeof(long);

#endif