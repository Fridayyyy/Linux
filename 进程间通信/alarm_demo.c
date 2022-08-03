#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc,char *argv[]){
    if (argc<2){
        printf("Usage: %s [seconds]\n", argv[0]);
        exit(0);
    }

    printf("I will sleep %d seconds!\n", atoi(argv[1]));

    alarm(atoi(argv[1]));
    pause();
    //当前没有设置信号处理函数，所以 Linux 采用默认处理方式将终结进程，所以后面的程序不会执行
    printf("xxxxxxxxxxx\n");
    return 0;
}
