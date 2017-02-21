#include<iostream>
using namespace std;
void Shu(long long num)
{
	if(num>=8)
		Shu(num/8);
	cout<<num%8;
}
int main()
{
	long long num;
	while(cin>>num)
	Shu(num);
	return 0;
}

