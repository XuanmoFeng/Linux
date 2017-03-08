#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int Start(int _port, const char *ip)
{
	int sock =socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket");
		exit(1);
	}
	struct sockaddr_in sockAdd;
	sockAdd.sin_family= AF_INET;
	sockAdd.sin_port=htons(_port);
	inet_aton(ip,&sockAdd.sin_addr);
	if( bind(sock,(struct sockaddr*)&sockAdd,sizeof(sockAdd)) < 0)
	{
		perror("bind");
		exit(2);
	}
	if(listen(sock,5))//给五个监听限制
	{
		perror("listen\n");
		exit(3);
	}
	return sock;
}
int main(int argc,char *argv[])
{

	if(argc!=3)
	{
		printf("Usg:%s [ip] [port]\n",argv[0]);
		return -1;
	}
	int port= atoi(argv[2]);
	int listen_sock = Start(port,argv[1]);
	struct sockaddr_in Clientsock;
	int sockfd;
	int len;
	while (1)
	{
		sockfd =accept(listen_sock,(struct sockaddr*)&Clientsock,&len);
		if(sockfd<0)
		{
			perror("accept");
			continue;
		}
		while(1)
		{
			char buf[1024];
			ssize_t _s = read(sockfd,buf,sizeof(buf)-1);
			buf[_s]=0;
			if(_s>0)
			{
				printf("Client##%s\n",buf);
			}
			else
			{
				printf("Client ip:: %s结束响应\n");
				break;
			}
		}
		close(sockfd);
	}
	return 0;
}
