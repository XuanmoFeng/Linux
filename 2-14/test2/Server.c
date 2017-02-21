#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
int main()
{ 
	int _i= mkfifo("./myfifo",S_IFIFO|0666);
	if(_i==0)
	{
		while(1)
		{
			char buf[1024];
			int _i = open("./myfifo",O_RDONLY);
			int sz=read(_i,buf,1024);
			if(sz)
			{
				buf[sz]='\0';
				printf("Clent:---->>:%s",buf);	
			}
			else
			{
				printf("over\n");
				break;
			}
		}

	}
	return 0;

}
