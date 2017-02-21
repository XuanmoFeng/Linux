#include "comm.h"
int main()
{
	int sem_id =creatShm();
	initShm(sem_id,0,1);
	pid_t id= fork();
	if(id==0)
	{
		while(1)
		{
			P(sem_id,0);
			usleep(1000);
			printf("A");
			usleep(1222);
			printf("A");
			fflush(stdout);
			V(sem_id,0);
		}
	}
	else
	{
		while(1)
		{
			P(sem_id,0);
			usleep(1600);
			printf("B");
			usleep(1003);
			printf("B");
			fflush(stdout);
			V(sem_id,0);			
		}
		wait(NULL);
	}
	destory(sem_id,0);
	return 0;
}
