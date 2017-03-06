#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
void *Pthread1(void *arg)
{
	int count=5;
	while(count--)
	{
		printf("this is Pthread1\n");
		sleep(1);
	}
	return ;
}
void *Pthread2(void *arg)
{
	int count=10;
	while(count--)
	{
		printf("this is Pthread2\n");
		sleep(1);
	}
}
int main()
{
	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread1,NULL,Pthread1,NULL);
	pthread_create(&thread2,NULL,Pthread2,NULL);
	pthread_join(thread2,NULL);
	pthread_join(thread1,NULL);
	printf(" this is main thread");
	return 0;
}
