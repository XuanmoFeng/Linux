#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
//#include <sys/type.h>
#include <stdlib.h>
#include <string.h>
int main()
{
	int fd[2]={0,0};
	pipe(fd);
	char buf[1024];
	pid_t id =fork();
	if(id==0)
	{
		char *buf="I am coder";
		int count=5;
		close(fd[0]);
		while(count--)
		{
			printf("child\n");
			write(fd[1],buf,strlen(buf));
			sleep(1);
		}
		printf("child is over \n");
	}else
	{
		close(fd[1]);
		int count =5;
		while(count--)
		{
			printf("father:\n");
			ssize_t  _sz=read(fd[0],buf,1024);
			buf[_sz]='\0';
			printf("father--:%s\n",buf);	
		}
		wait(NULL);
	}
	return 0;

}
