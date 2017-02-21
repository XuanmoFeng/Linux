#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <unistd.h>
typedef struct Node
{
	int data;
	struct Node *next;
}Node_t,*Node_p,**Node_pp;

pthread_mutex_t mutex;
pthread_cond_t cond =PTHREAD_COND_INITIALIZER;

Node_p Alloc()
{
		Node_p newNode =(Node_p)malloc(sizeof(Node_t));
		newNode->next=NULL;
		return newNode;
}
Node_p Init(int data)
{
	Node_p newNode =Alloc();
	newNode->data =data;
	newNode->next=NULL;
	return newNode;
}
void Push(Node_p list,int data)
{
	Node_p newNode =Alloc();
	newNode->next=list->next;
	newNode->data=data;
	list->next=newNode;

}
void Pop(Node_p list)
{
	assert(list);
	Node_p newNode=list->next;
	list->next=newNode->next;
	free(newNode);
	newNode=NULL;
}

int empty(Node_p list)
{
	if(list->next==NULL)
		return 1;
	return 0;
}

void *Pro(void* arg)
{
		Node_p list =(Node_p)arg;
		while(1)
		{

			pthread_mutex_lock(&mutex);
			
			pthread_cond_signal(&cond);
			int data = rand()%40;
			if(empty(list))
			{
				Push(list ,data);
				sleep(1);
				printf("Pro:%d\n",list->next->data);	
			
			}
			pthread_mutex_unlock(&mutex);
		}
}

void *Con(void *arg)
{
	Node_p list = (Node_p) arg;
	Node_p newNode= list->next;
		while(1)
		{
			pthread_mutex_lock(&mutex);
			if(empty(list))
			{	
					
				while(pthread_cond_wait(&cond,&mutex)==0)
				{
					printf("Con::%d\n",list->next->data);
					pthread_cond_signal(&cond);
					Pop(list);
				}
			}
			pthread_mutex_unlock(&mutex);
			printf("COn\n");
		}
}
void Test()
{
	Node_p head =NULL;
	head= Init((int)(&head));
	Push(head,2);
	Push(head,1);
	printf("ll:%d\n",head->data);
	printf("ii:%d\n",head->next->data);
	Pop(head);
	printf("ii:%d\n",head->next->data);
}
int main()
{
	Node_p head =NULL;
	
	head= Init((int)(&head));
	pthread_t thread1;
	pthread_t thread2;
	pthread_create(&thread2,NULL,Pro,head);

	pthread_create(&thread1,NULL,Con,head);	
	pthread_join(thread1,NULL);
	pthread_join(thread2,NULL);
	pthread_mutex_destroy(&mutex);
	pthread_cond_destroy(&cond);
	return 0;
}
