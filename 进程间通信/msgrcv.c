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

    if ((key= ftok(".",'a'))==-1){
        perror("ftok: ");
        exit(1);
    }

    qid = msgget(key,IPC_CREAT|0666);
    if (qid==-1){
        perror("msgget");
        exit(1);
    }
    printf("open msg queue %d\n",qid);

    do {
        memset(msg.msg_text,0,BUFFER_SIEZ);
        if (msgrcv(qid,(void*)&msg,BUFFER_SIEZ,0,0)<0){
            perror("msgrcv");
            exit(1);
        }
        printf("The message from process %ld : %s\n", msg.msg_type, msg.msg_text);

    } while (strcmp(msg.msg_text,"q")&& strcmp(msg.msg_text,"Q"));

    printf("remove the queue %d from kernel!\n",qid);
    if ((msgctl(qid,IPC_RMID,NULL))<0){
        perror("msgctl");
        exit(1);
    }
    return 0;
}
