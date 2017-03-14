#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(int argc, char *argv[])
{
	if(argc!=3)
	{
		printf("格式如下:%s [local_ip] [local_port]\n",argv[0]);
		return 1;	
	}
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in Client;
	Client.sin_family =AF_INET;
	Client.sin_port=htons(atoi(argv[2]));
	Client.sin_addr.s_addr=inet_addr(argv[1]);
		char buf[1024];
	while(1)
	{
		printf("Client##");
		fflush(stdout);
		//	printf("Client##");
		ssize_t _sz=read(0,buf,sizeof(buf));
		buf[_sz-1]=0;
		socklen_t len=sizeof(Client);
		ssize_t sz=sendto(sock,buf,sizeof(buf),0,(struct sockaddr*)&Client,len);
	}
	close(sock);

	return 0;
}
