#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    pid_t pid;
    int ret = 0;

    pid = fork();
    if (pid<0){
        perror("fork error.");
        exit(1);
    } else if (pid==0){
        printf("I am child progress, pid[%d], I recive any signal\n", getpid());

        raise(SIGSTOP);
        printf("I am child progress, I resume run...\n");//由于前面的STOP 信号，子进程执行不到这里
        printf("I am child progress, I Quit.\n");
        exit(0);

    } else{
        sleep(2);
        if ((waitpid(pid,NULL,WNOHANG))==0){
            printf("I am parent progress [%d], I send signal to my child [%d]\n", getpid(), pid);

            kill(pid, SIGCONT);//发送信号让子进程继续执行

        }
        waitpid(pid, NULL, 0);
        printf("I am parent progress, I recv child progress quit, I quit!\n");

        return 0;
    }
}