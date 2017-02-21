#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
int main()
{ 
		//fflush(stdout);
		char buf[1024];
		int _i = open("./myfifo",O_WRONLY);
		while(1)
		{
			printf("shuru-->:");
			fflush(stdout);
			int sz=read(1,buf,1024);
			buf[sz]='\0';
			write(_i,buf,strlen(buf));
			sleep(1);


		}

	
	return 0;

}
