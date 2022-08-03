#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define DELAY_TIME  3
union semun{
    int val;
    struct semid_ds *buf;
    unsigned short *array;
};
int init_sem(int sem_id,int init_val){
    union semun sem_union;
    sem_union.val = init_val;
    if (semctl(sem_id,0,SETVAL,sem_union)==-1){
        perror("init samaphore error");
        return -1;
    }
    return 0;
}
int del_sem(int sem_id){
    union semun,sem_union;
    if (semctl(sem_id,0,IPC_RMID,sem_union) == -1){
        return -1;
    }
    return 0;
}
int sem_p(int sem_id){
    struct sembuf sem_b;
    sem_b.sem_num = 0;
}