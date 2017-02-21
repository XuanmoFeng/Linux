#include "comm.h"
int main()
{
	int id = createmsgQueue();
	if(id<0)
	{
		printf("main faile\n");
	}
	char buf[128];
	while(1)
	{
		printf("等待中..\n");
		int ret=reciveMessage(id,buf,CLENT_TYPE);
		if(ret <0)
		{
			perror("RECEVERMessage");
			return -4;
		}
		buf[ret]='\0';
		printf("clent say:%s",buf);
		sendMessage(id,buf,CLENT_TYPE);
	}
	destory(id);
	return 0;

}
