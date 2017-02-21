#include "comm.h"
static int commShm(int flag)
{
	key_t id =ftok(PATHNAME,FLAG);
	if(id <0)
	{
		perror("ftok");
		return -1;
	}
	int ret = shmget(id,SIZE,flag);
	if(ret <0)
	{
		perror("shmget");
	}
	return ret;
}
int creatShm()
{
	return commShm(IPC_CREAT|IPC_EXCL|0666);

}
int getShm()
{
	return commShm(IPC_CREAT);
}
/*char *shmAt(int shmid)
{

 char *ret= (char *)shmat(shmid,NULL,0);
	return &ret;
}
int shmDt(void *mem)
{
	int ret= shmdt(mem);
	if(ret<0)
	{
		perror("shmDt");
		return -2;
	}
	return ret;
}*/
int destory(int shmid)
{
	int ret = shmctl(shmid,IPC_RMID,NULL);
	if(ret<0)
	{
		perror("destory");
		return -3;
	}
	return ret;
}
