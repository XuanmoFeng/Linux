/*************************************************************************
> File Name: server.c
> Author:FENGKAI 
> Mail: 763608087@qq.com
> Created Time: 2017年03月17日 星期五 23时27分35秒
************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<netinet/in.h>
#include<poll.h>

#define POLLSIZE 3

static clientnum =-1;
int Start(char *_ip,int _port)
{
    int  sock=socket(AF_INET,SOCK_STREAM,0);
    if(sock<0)
    {
        perror("socket");
        return 1;
    }
    int  reuse;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(reuse));
    struct sockaddr_in server;
    server.sin_family =AF_INET;
    server.sin_port=htons(_port);
    server.sin_addr.s_addr=inet_addr(_ip);
    if( bind(sock,(struct sockaddr*)&server,sizeof(server))<0)
    {
        perror("bind");
        return 2;
    }
    if(listen(sock,5)<0)
    {
        perror("listen");
        return 3;
    }
    return sock;
}
int main(int argc ,char *argv[])
{
    if(argc!=3)
    {
        printf("Using:%s[ip][port]\n",argv[0]) ;
        return 4;
    }
    int  sock= Start(argv[1],atoi(argv[2]));
    struct pollfd _pol[POLLSIZE];
    _pol[0].fd=sock;
    _pol[0].events =POLLIN|POLLOUT;
    _pol[0].revents=0;
    int i=0;
    for(i =1;i<POLLSIZE;i++)
    {
        _pol[i].fd=-1;
        _pol[i].events =POLLIN|POLLOUT;
        _pol[i].revents=0;
    }
    int timeout=5000;
    while(1)
    {
        int ret;
        switch(ret=poll(_pol,POLLSIZE,timeout))
        {
            case 0:
            printf("time out\n");
            break ;
            case -1:
            printf("poll error\n");
            break;
            default:
            {
                int pollsock;
                struct sockaddr_in clent;
                clent.sin_family =AF_INET;
                socklen_t len =sizeof(clent);
                pollsock= accept(sock,(struct sockaddr*)&clent,&len);
                printf("clent:: %s  is online\n",inet_ntoa(clent.sin_addr));
                if(_pol[0].revents&(POLLIN|POLLOUT))
                {
                    int i=0;
                    for(;i<POLLSIZE;i++)
                    {
                        if(_pol[i].fd<0)
                        {
                            _pol[i].fd=pollsock;
                            break;
                        }
                    }
                    _pol[i].events=POLLIN;
                }
                for(i=1;i<POLLSIZE;i++)
                {
                    if(_pol[i].fd<0)
                        continue;
                    while(1)
                    {
                        char buf[1024];
                        ssize_t sz=-1;
                        fflush(stdin);
                        sz =read(_pol[i].fd,buf,1024);
                        if(sz<=0){
                            printf("quit\n") ;
                            break;
                        }
                        else{
                            buf[sz-1]=0;
                            printf("clent:%s\n",buf);
                        }
                    }
                }
            }
            break;
        }
    }
    return 0;
}

