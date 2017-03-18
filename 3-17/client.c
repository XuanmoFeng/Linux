#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
int main(int argc,char* argv[])
{
	int sock = socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("clent socket");
		return -1;
	}
	struct sockaddr_in clientSock;
	clientSock.sin_family = AF_INET;
	clientSock.sin_port =htons(atoi(argv[2]));
	clientSock.sin_addr.s_addr=inet_addr(argv[1]);
	
	if (connect(sock,(struct sockaddr*)&clientSock,sizeof(clientSock)) < 0)
	{
		perror("clent connect");
		return -2;
	}
	while(1)
	{
		printf("send##");
		fflush(stdout);
		char buf[1024];
		ssize_t _s =read(0,buf,sizeof(buf));
		buf[_s-1]='\0';
		write(sock,buf,_s);
	}
	close(sock);
	return 0;
}
