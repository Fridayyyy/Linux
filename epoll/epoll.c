#include <sys/epoll.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc,char *argc[]){
    int ret;
    int fd;

    ret= mkfifo("test_fifo",0666);
    if (ret!=0){
        perror("mkfifo: ");
    }

    fd= open("test_fifo",O_RDWR);
    if (fd<0){
        perror("open fifo");
        return -1;
    }
    ret=0;
    struct epoll_event event;
    struct epoll_event wait_event;

    int epfd = epoll_create(10);
    if (epfd==-1){
        perror("epoll_create");
        return -1;
    }

    event.data.fd=0;
    event.events=EPOLLIN;//对应的文件描述符可以读；

    ret=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
    if (ret==-1){
        perror("epoll_ctl");
        return -1;
    }
    ret=0;
    while (1){
        ret=epoll_wait(epfd,&wait_event,2,-1);
        if (ret==-1){
            close(epfd);
            perror("epoll");
        } else if (ret>0){
            char buf[100]={0};
            if ((0==wait_event.data.fd)&&
                    (EPOLLIN == wait_event.events & EPOLLIN)){
                read(0,buf,sizeof(buf));
                printf("stdin buf = %s\n", buf);
            } else if ((fd==wait_event.data.fd)&&
                    (EPOLLIN==wait_event.events & EPOLLIN)){
                read(fd,buf, sizeof(buf));
                printf("fifo buf = %s\n", buf)
            }
        } else if (0==ret){
            printf("time out\n");
        }
    }
    close(epfd);
    return 0;
}