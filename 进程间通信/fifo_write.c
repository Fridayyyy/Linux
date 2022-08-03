//
// Created by 常贵杰 on 2022/7/30.
//
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
    int nwrite;

    fd = open(FIFO_NAME,O_WRONLY);
    if (fd==-1){
        printf("open error\n");
        exit(1);
    }

    while (1){
        memset(buff,0,MAX_BUFFER_SIZE);
        printf("请输入： （q/Q退出）\n");
        scanf("%s",buff);

        if (!strcmp(buff,"q")||!strcmp(buff,"Q")){
            printf("[%d] write fifo 程序退出...",getpid());
            break;
        }
        nwrite = write(fd,buff, strlen(buff)+1);

        if (nwrite>0){
            printf("write '%s' to fifo\n",buff);
        } else{
            printf("write error...\n");
            break;
        }
    }
    close(fd);
    return 0;
}


