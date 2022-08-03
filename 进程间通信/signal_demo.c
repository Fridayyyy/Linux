#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void my_signal_back(int sign_no){
    if (sign_no==SIGINT){
        printf("[%d]I recv signal [ SIGINT ]!\n", getpid());
    } else if (sign_no == SIGQUIT){
        printf("[%d]I recv signal [ SIGQUIT ]!\n", getpid());
    } else{
        //printf(" this  %s"sign_no);
    }
}
int main(int argc,char *argv[]){
    signal(SIGINT,my_signal_back);
    //signal(2,my_signal_back);
    signal(SIGQUIT,my_signal_back);
    printf("[%d]Waiting for signal SIGINT or SIGQUIT...\n", getpid());

    pause();
    printf("quit...\n");
    return 0;
}