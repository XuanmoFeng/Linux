#include<stdio.h>
#include<unistd.h>
void probar()
{
	int rate=0;//进度率，表示我们这个进度走了%多少了
	char bar[102]={0};//0-100应该101个，为什么会102个呢，因为第102个我们给他设置为空。
	//0我们不打印“=”
	const char *sta="-\\|/";//有时间我们看进度条不知道它是卡了
	//还是在运行呢，所以我们就见后面有个圆圈的一样的东西在闪
	//我们也是设置一个这样的好区别我们的程序是卡了还是在运行
	while(rate <= 100)
	{
		printf("[%-100s]%d%%[%c]\r",bar,rate,sta[rate%4]);
		usleep(9500);//休眠时间sleep(second)参数是秒，库为unistd.h，还有一个休眠函数usleep(mircsecond);它的参数为微秒
		fflush(stdout);
		bar[rate]= '=';
		rate++;
		bar[rate]='\0';
	}
	printf("\ncomplate!!\n");

}
int main()
{
	probar();
	return 0;
}
