#include "comm.h"
static int comShm(int flag)
{
	key_t id = ftok(PATHNAME,FLAG);
	if(id<0)
	{
		perror("ftok");
		return -1;
	}
	int shmid = semget(id,1,flag);
	if(shmid<0)
	{
		perror("semget");
		return -2;
	}
	return shmid;
}
int creatShm()
{
	return comShm(IPC_CREAT|IPC_EXCL|0666);
}

	//initShm(sem_id,1,0);
int initShm(int sem_id,int which,int value)
{
	union semun se;
	se.val= value;
	//se.array=1;
	int ret =semctl(sem_id,which,SETVAL,se);

	if(ret<0)
	{
		perror("semctl");
		return -1;
	}
	return ret;
}
int P(int id,int which)
{
	struct sembuf sem;
	sem.sem_num =which;
	sem.sem_op=-1;
	sem.sem_flg=0;
	int ret = semop(id,&sem,1);
	if(ret<0)
	{
		perror("P error");
		return -4;
	}
	return ret;	
}
int getShm()
{
	return comShm(IPC_CREAT);
}

int V(int id ,int which)
{
	struct sembuf sem;
	sem.sem_num =which;
	sem.sem_op=1;
	sem.sem_flg=0;
	int ret =semop(id,&sem,1);
	if(ret <0)
	{
		perror("V error");
		return -5;
	}
	return ret;
}
int destory(int id,int which)
{
	int ret=semctl(id,which,IPC_RMID);
	if(ret<0)
	{
		perror("semctl");
		return -3;
	}
	return ret;
}
