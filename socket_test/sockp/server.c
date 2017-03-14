#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<errno.h>
#include<netinet/in.h>
#include<string.h>
#include<stdio.h>

#define PORT "8080"
#define IP "0"

void  start()
{
	int fd[2];
	int ret ;
	ret = socketpair(AF_UNIX,SOCK_STREAM,0,fd);
	if(ret<0)
	{
		printf("sockpair");
		return ;
	}
	int id= fork();
	if(id==0)
	{
			char buf[1024]="qwwe\n";
			write(fd[1],buf,sizeof(buf));
			sleep(2);
			printf("father::%s\n",buf);
			exit(0);
	}
	else
	{
			close(fd[1]);
			char buf[1024];
			ssize_t sz=read(fd[0],buf,1024);
			if(sz<0)
			{
				printf("quit\n");
			}
			else
			{
				buf[sz]=0;
				printf("child::%s",buf);
			}
			wait(NULL);
	}
}
int main()
{
	start();
	return 0;
}
