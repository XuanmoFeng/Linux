#include<stdio.h>
#include<stdlib.h>
typedef struct Node
{
	int data;
	struct Node* next;
}*LinkList,LinkNode;
void CreateList(LinkList *L,const int n)
{
	LinkList p;
	int i;
	*L=(LinkList)malloc(sizeof(LinkNode));
	(*L)->next =NULL;
	for(i=0;i<n;i++)
	{
		p=(LinkList)malloc(sizeof(LinkNode));
		p->data=rand()%10;
		p->next=(*L)->next;
		(*L)->next=p;
	}
}
void Display(LinkList *L)
{
	if((*L)->next==NULL)
	{
		printf("empty\n");
		return ;
	}
	LinkList p =(*L)->next;
	while(p!=NULL)
	{
		printf("%d\t",p->data);
		p=p->next;
	}
}
int main()
{
	LinkList L =NULL;
	CreateList(&L,2);
	Display(&L);
	return 0;
}
