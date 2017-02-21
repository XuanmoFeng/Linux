#include"comm.h"
int main()
{
	int shmid =creatShm();
	char *mem=(char*)shmat(shmid,NULL,0);
	int i=0;
	int count=5;	
	while(count--)
	{
		printf("%s\n",mem);
		sleep(1);
	}
	shmdt(mem);
	sleep(5);
	destory(shmid);
	return 0;

}
