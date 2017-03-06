#include<stdio.h>
#include<unistd.h>
#include <signal.h>

void Sleep(int second)
{
	//NULL

}
int main()
{

	
	sigset_t newset;
	sigemptyset(&newset);
	struct sigaction *set,*oldset;
	set->sa_handler = Sleep;
	set->sa_flags=0;
	set->sa_mask=newset;
	sigaction(SIGALRM,set,oldset);
	while(1)
	{
		alarm(1);
		pause();
		printf("hello\n");
	}
	sigaction(SIGALRM,oldset,NULL);
	return 0;
}
