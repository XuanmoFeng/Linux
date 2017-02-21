
#ifndef _COMM_
#define _COMM_
#include<stdio.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#define MES_SIZE 128
#define SERVER_TYPE 0
#define CLENT_TYPE 1
struct msgbuf
{
	long type;
	char msg[MES_SIZE];
};
int createmsgQueue();
int getmsgQueue();
int sendMessage(int id ,char *buf,int type);
int recievMessage(int id ,void *buf ,int type);
int destory(int id);

#endif 
