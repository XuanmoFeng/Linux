#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<errno.h>
//#include<error.c>
#define FIFE_MODE (S_IRUSR |S_IWUSR|S_IRGRP|S_IROTH)
#define FIFO1 "./fifo.1"
#define FIFO2 "./fifo.2"

void clent(int ,int);
void server(int ,int);
int main()
{
	int readfd,writefd;
	pid_t childpid;
	if((mkfifo(FIFO1,FIFE_MODE)<0)&&(errno!=EEXIST))
		strerror("cant create %s",FIFO1);

	if((mkfifo(FIFO2,FIFE_MODE)<0)&&(errno!=EEXIST))
	{
		unlink(FIFO1);
		strerror("cant create %s",FIFO2);
	}
	if((childpid=fork())==0)
	{
		//child
		readfd=open(FIFO1,O_RDONLY,0);
		writefd =open(FIFO2,O_WRONLY,0);

		server(readfd,writefd);
		exit(0);
	}
	//father
	writefd =open(FIFO1,O_WRONLY,0);
	readfd =open(FIFO2,O_RDONLY,0);
	clent(readfd,writefd);
	waitpid(childpid,NULL,0);
	close(readfd);
	close(writefd);
	unlink(FIFO1);
	unlink(FIFO2);
	exit(0);

	return 0;

}
