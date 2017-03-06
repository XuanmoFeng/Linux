#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
int main()
{
	pid_t id = fork();
	if(id ==0)
	{
		sleep(60);
		printf("new\n");
		exit(0);
	}
	else
	{
	printf("main\n");
	wait(NULL);
	}
	return 0;
}
