#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUFFER_SIEZ 256

typedef struct message{
    long msg_type;
    char msg_text[BUFFER_SIEZ];
}message_t;

int main(){
    int qid;
    key_t key;
    message_t msg;

    if ((key = ftok(".",'a'))==-1){
        perror("ftok: ");
        exit(1);
    }

    qid = msgget(key,IPC_CREAT|0666);
    if (qid==-1){
        exit(1);
    }

    printf("Open msg queue %d\n", qid);

    while (1){
        printf("Input snd msg to the queue(q or Q for quit):\n");

        if ((fgets(msg.msg_text,BUFFER_SIEZ,stdin))==NULL){
            printf("No message!\n");
            exit(1);
        }

        msg.msg_type = getpid();
        if ((msgsnd(qid,&msg, strlen(msg.msg_text),0))<0){
            perror("message posted");
            exit(1);
        }
        if (!strcmp(msg.msg_text,"q")||!strcmp(msg.msg_text,"Q")){
            printf("quit func...");
            break;
        }
    }
    return 0;
}
