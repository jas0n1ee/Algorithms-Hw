#include<iostream>
#include<fstream>
#include<cstring> 
using namespace std;
int c2i(char *x)
{
	int s=strlen(x);
	int r=0;
	for(int i=0;i<s;i++) r=r*10+x[i]-'0';
	return r;
}
int main(int argc,char *argv[])
{
	ofstream outfile(argv[2],ios::out|ios::trunc);
	int N=c2i(argv[1]);
	if(N)
	{
		int *data=new int[N];
		int num=1,flag=0;
		data[0]=2;
		outfile<<"2\n";
		for(int i=3;;i+=2)
		{
			flag=0;
			for(int j=0;j<num;j++)
			{
				if(i%data[j]==0) 
				{	flag=1;
					break;
				}
			}
			if(flag==0) 
			{
				outfile<<i<<endl;
				data[num]=i;
				num++;
			}
			if(num==N) break;
		}
		delete [] data;
	}
	outfile.close();
	return 0;
}

