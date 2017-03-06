#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<signal.h>

void Mydaemon()
{
	umask(0);
	if(fork()>0)
	{
		exit(1);
	}
	setsid();
	chdir("/");
	close(0);
	close(1);
	close(2);
	signal(SIGCHLD,SIG_IGN);
}

int main()
{
	Mydaemon();
	while(1);
	return 0;
}
