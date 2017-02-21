#include "comm.h"
int main()
{
	int shmid = getShm();
	char *mem =(char*)shmat(shmid,NULL,0);
	int count=5;
	int i=0;
	while(count--)
	{
		mem[i++]='A';
		mem[i]='\0';
		sleep(1);
	}
	shmdt(mem);
	return 0;
}
