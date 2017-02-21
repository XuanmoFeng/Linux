#ifndef _COMM_
#define _COMM_
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include<unistd.h>
#define PATHNAME "."
#define FLAG 0x666
#define SIZE 4096*2
int creatShm();
int getShm();
//char *shmAt(int shm_id);
//int shmDt(void* mem);
int destory(int shm_id);


#endif
