#include "comm.h"
int main()
{
	//printf("server`");
	int id = getmsgQueue();
	if(id<0)
	{
		printf("main faile\n");
	}
	char buf[128];
	while(1)
	{
		printf("clent#");
		fflush(stdout);
		int sz=read(0,buf,1024);
		buf[sz]='\0';
		sendMessage(id,buf,CLENT_TYPE);
		char buf2[128];
		if(reciveMessage(id,buf2,SERVER_TYPE)>0)
		{
			printf("server::%s",buf2);
		}
	}
	return 0;

}
