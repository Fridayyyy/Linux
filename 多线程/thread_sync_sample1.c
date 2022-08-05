//
// Created by 常贵杰 on 2022/8/3.
//
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <errno.h>
static int glob = 0;
static pthread_mutex_t mtx = PTHREAD_MUTEX_INITIALIZER;


static void *thread_routine(void *arg){
    int loc,j;
    for (j = 0; j < 10000000; j++) {
        pthread_mutex_lock(&mtx);
        loc = glob;
        loc++;
        glob=loc;
        pthread_mutex_unlock(&mtx);
    }
    return NULL;
}

int main(int argc,char *argv[]){
    pthread_t t1,t2;
    int s;

    s= pthread_create(&t1,NULL,thread_routine,NULL);
    if (s!=0)
        printf("error");
    s= pthread_create(&t2,NULL,thread_routine,NULL);
    if (s!=0)
        printf("error");

    s= pthread_join(t1,NULL);

    s= pthread_join(t2,NULL);

    printf("glob = %d\n",glob);
    exit(EXIT_SUCCESS);
}

