#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

#define _SIZE_ 64


sem_t block;
sem_t CountNum;
pthread_mutex_t mutex;
pthread_mutex_t mutex1;
int Count[_SIZE_];
void *Con_Run(void *arg)
{
	static	int i=0;
	while(1)
	{
		sleep(1);
		pthread_mutex_lock(&mutex);
		sem_wait(&CountNum);
		printf("Con::%d\n",Count[i]);
		i++;
		i%=_SIZE_;
		sem_post(&block);
		pthread_mutex_unlock(&mutex);
	}
}
void *Pro_Run(void *arg)
{
	static int i=0;
	while(1)
	{
		sleep(2);
		pthread_mutex_lock(&mutex1);
		sem_wait(&block);
		int Data = rand()%45;
		Count[i++]=Data;
		printf("PRO::%d\n",Data);
		i%=_SIZE_;
		sem_post(&CountNum);
		pthread_mutex_unlock(&mutex1);
	}
}
int main()
{
	sem_init(&CountNum,0,0);
	sem_init(&block,0,_SIZE_);
	pthread_t Pro_1;
	pthread_t Pro;
	pthread_t Con;
	pthread_t Con_1;
	pthread_create(&Pro_1,NULL,Pro_Run,NULL);
	pthread_create(&Pro,NULL,Pro_Run,NULL);
	pthread_create(&Con_1,NULL,Con_Run,NULL);
	pthread_create(&Con,NULL,Con_Run,NULL);
	pthread_join(Pro_1,NULL);
	pthread_join(Con_1,NULL);
	pthread_join(Pro,NULL);
	pthread_join(Con,NULL);
	sem_destroy(&block);
	sem_destroy(&CountNum);
	return 0;
}
