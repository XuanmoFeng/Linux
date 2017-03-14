#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("格式如下:%s [local_ip] [local_port]\n",argv[0]);
		return 1;	
	}
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0)
	
		printf("socket error");
		return 2;
	}
	int reuse;
	//setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
	struct sockaddr_in server;
	server.sin_family= AF_INET;
	server.sin_port=htons(atoi(argv[2]));
	server.sin_addr.s_addr =inet_addr(argv[1]);
	if(bind(sock,(struct sockaddr *)&server,sizeof(server))<0)
	{
		printf("bind error\n");
		return 3;
	}

	char buf[1024];
	struct sockaddr_in Client;
	socklen_t len=sizeof(Client);
	while(1)
	{
		ssize_t sz=recvfrom(sock,buf,sizeof(buf),0,(struct sockaddr *)&Client,&len);
		buf[sz-1]=0;
		printf("Client#: %s",buf);
	}
	close(sock);
	return 0;
}
