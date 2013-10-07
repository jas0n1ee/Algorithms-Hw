#include<iostream>
#include<fstream>
using namespace std;
int main()
{
	int t[2];
	int count=0;
	char rout1[10]="r1.txt";
	char rout2[10]="c1.txt";
	fstream out("result.txt",ios::out|ios::trunc);
	for(int i=1;i<6;i++)
	{
		rout1[1]=i+48;
		rout2[1]=i+48;
		fstream r(rout1,ios::in);
		fstream c(rout2,ios::in);
		if(!(r&&c)) break;
		while((!r.eof())&&(!c.eof()))	
		{
			if(r>>t[0]&&c>>t[1])
			{
				if(t[0]==t[1])
				{
					out<<"Right\t";
				}
				else out<<"Wrong\t";
				count++;
				if(count%3==0) out<<endl;
			}
		}
		r.close();
		c.close();
		out<<endl;
	}
	out.close();
}
