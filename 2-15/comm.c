#include "comm.h"
static int commQueue(int type)
{
	key_t key=ftok(".",0);
	if(key<0)
	{
		perror("ftok");
		return -1;
	}
	int id = msgget(key,type);
	if(id<0)
	{
		perror("msgget");
		return -2;
	}
	return id;
	
}
int createmsgQueue()
{
	return commQueue(IPC_CREAT |IPC_EXCL | 0666);
}
int getmsgQueue()
{
	return commQueue(IPC_CREAT);
}
int sendMessage(int id,char _buf[128],int type)
{
	struct msgbuf buf;
	strcpy(buf.msg,_buf);
	buf.type = type;
	if(msgsnd(id,&buf,strlen(buf.msg),0)<0)
	{
		perror("sendMessage");
		return -1;
	}
	return 1;
}
int reciveMessage(int id,char _buf[128], int type)
{
	struct msgbuf buf;
	ssize_t _sz=msgrcv(id,&buf,strlen(buf.msg),type,0);
	if (_sz<0)
	{
		perror("reciverMessage");
	}	
	buf.msg[_sz]='\0';
	strcpy(_buf,buf.msg);
	return _sz;
}
int destory(int id)
{
 int ret =msgctl(id,IPC_RMID,0);
 if(ret <0)
 {
	 perror("destory");
	 return -3;
 }
 printf("destory\n");
}
