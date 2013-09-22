#include<iostream>
#include<fstream>
using namespace std;
int main(int argc,char*argv[])
{
	fstream infile(argv[1],ios::in);
	fstream outfile(argv[2],ios::out|ios::trunc);
	while(1)
	{
		char t=infile.get();
		if(t==-1) break;
		else if((t>='a'&&t<='z')||(t>='A'&&t<='Z')||(t>='0'&&t<='9')) outfile<<(char)(t+5);
		else outfile<<(char)(t-3);
	}
	infile.close();
	outfile.close();
	return 0;
}
