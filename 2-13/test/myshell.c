#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
	while(1)
	{
		//printf("[a@localhost 2-13]#");
		pid_t id =fork();
		if(id)
		{
			execl("/home/a/cmd/2-13/mytest","./mytest");
		}
		else
		{
			printf("[a@localhost ????]# ");
		}
	}
	return 0;
}
