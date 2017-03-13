//#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<stdlib.h>
#include<errno.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<stdio.h>
int Start(char *_ip,int _port)
{
	int sock =socket(AF_INET,SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket\n");
		return 1;
	}
	int reuse=1;
	struct sockaddr_in server;
	server.sin_family= AF_INET;
	server.sin_port = htons(_port);
	server.sin_addr.s_addr =inet_addr(_ip);
	if(bind(sock,(struct sockaddr*)&server,sizeof(server))<0)
	{
		perror("bind\n");
		return 2;
	}
	if(listen(sock,5)<0)
	{
		perror("listen\n");
		return 3;
	}
	return sock;
}
void *Accept(void *argv)
{
	//pthread_detach(pthread_self());
	int sock = (int)(*((int*) argv));
	while(1)
	{
		char buf[1024];
		ssize_t sz=read(sock,buf,sizeof(buf)-1);
		if(sz<0)
		{
			printf("quit!!\n");
		}
		else
		{
			fflush(NULL);
			buf[sz-1]=0;
			sz=write(sock,buf,sizeof(buf));
			printf("client## %s\n",buf);
		}
	}
//	return ;
	close(sock);
}
int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("useage:%s[server_ip][server_port]",argv[0]);
		return 6;
	}
	char *ip =argv[1];
	int port=atoi(argv[2]);
	int lisensock =Start(ip,port);
	int reuse;
	setsockopt(lisensock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	pthread_t id;
	pthread_t id2;
	struct sockaddr_in client;
	socklen_t len= sizeof(client); 
	while(1)
	{
		int sock =accept(lisensock,(struct sockaddr*)&client,&len);
		if(sock<0)
		{
			continue;
		}
		else
		{
			pthread_create(&id,NULL,Accept,&sock);
			pthread_detach(id);
			pthread_create(&id2,NULL,Accept,&sock);
		}
	}
	close(lisensock);
	return 0;
}
