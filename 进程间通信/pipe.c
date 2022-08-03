#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_DATA_LEN    128
#define DELAY_TIME      3

int main(){
    pid_t pid;
    int pipe_fd[2];
    char buf[MAX_DATA_LEN];
    const char data[] = "pipe demo program";
    int real_read;
    int real_write;

    memset((void *)buf,0,sizeof(buf));
    if (pipe(pipe_fd)<0){
        printf("pipe create error\n");
        exit(1);
    }

    pid = fork();

    if (pid==0){
        close(pipe_fd[1]);
        sleep(DELAY_TIME);

        real_read = read(pipe_fd[0],buf,MAX_DATA_LEN);

        if (real_read>0){
            printf("Child progress : read %d bytes from the pipe : '%s' \n", real_read, buf);

        }

        close(pipe_fd[0]);
        exit(0);
    } else if (pid>0){
        close(pipe_fd[0]);
        sleep(DELAY_TIME);

        real_write = write(pipe_fd[1],data, strlen(data));
        if (real_write!=-1){
            printf("Parent progress : write %d bytes to the pipe : '%s' \n", real_write, data);

        }

        close(pipe_fd[1]);
        waitpid(pid,NULL,0);
    }
    return 0;
}
