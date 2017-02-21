#include"comm.c"
void *funTh1(void * buef)
{
	printf("new thread\n");
	int buf;
	pthread_exit((void *)&buf);
}
void *funTh2(void *buf)
{
	printf("thread 2\n");
	return NULL;
}
void *funTh3(void *buf)
{
	printf("thread 3\n");
	
}
int main()
{
	pthread_t thread1;
	pthread_create(&thread1,NULL,funTh1,NULL);
	pthread_join(thread1,NULL);	
	pthread_t thread2;
	pthread_create(&thread2,NULL,funTh2,NULL);
	pthread_t thread3;
	pthread_create(&thread3,NULL,funTh3,NULL);
	pthread_cancel(thread3);	
	pthread_join(thread2,NULL);
	printf("main ");
	return 0;
}
