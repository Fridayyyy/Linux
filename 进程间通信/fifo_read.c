#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <unistd.h>

#define FIFO_NAME    "/tmp/demo_fifo"    /* 有名管道名称 */
#define MAX_BUFFER_SIZE     PIPE_BUF     /* 定义数据长度，使用 limits.h 中的 PIPE_BUF 长度 */

int main(int argc,char *argv[]){
    int fd;
    char buff[MAX_BUFFER_SIZE];
    int nread;

    if (access(FIFO_NAME,F_OK)==-1){
        if ((mkfifo(FIFO_NAME,0666)<0)&&(errno!=EEXIST)){
            exit(1);
        }
    }

    fd = open(FIFO_NAME,O_RDONLY);
    if (fd==-1){
        printf("open error \n");
        exit(1);
    }

    while (1){
        memset(buff,0,MAX_BUFFER_SIZE);
        nread = read(fd,buff,MAX_BUFFER_SIZE);

        if (!strcmp(buff,"q")||!strcmp(buff,"Q")){
            printf("[%d] 程序退出 ",getpid());
            break;
        }
        if (nread>0){
            printf("read '%s' from fifo\n",buff);
        } else{
            printf("read error\n");
            break;
        }
    }
    close(fd);
    return 0;
}



