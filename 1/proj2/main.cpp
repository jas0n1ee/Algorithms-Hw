#include<iostream>
using namespace std;
int main(int argc,char*argv[])
{
	while(1)
	{
		char t=cin.get();
		if(t==-1) break;
		else if((t>='a'&&t<='z')||(t>='A'&&t<='Z')||(t>='0'&&t<='9')) cout<<(char)(t+5);
		else cout<<(char)(t-3);
	}
	return 0;
}
