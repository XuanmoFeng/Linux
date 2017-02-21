#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main ()
{

		char * myargv[10];
		char buf[1024];
		ssize_t p = read(0,buf,1024);
		buf[p-1]='\0';
		pid_t id =fork();
		if(id)
		{
			myargv[0]=buf;
			int i =1;
			char *start = buf;
			while(*start!='\0')
			{
				if(*start==' ')
				{
					*start='\0';
					start++;
					myargv[i++]=start;
				}
				else
				{
					start++;
				}
			}
			myargv[i]=NULL;
			execvp(myargv[0],myargv);
		}else
		{
			wait(NULL);
		}
	return 0;
}
