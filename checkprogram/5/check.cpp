#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
using namespace std;
int main()
{
	char rout1[10]="r1.txt";
	char rout2[10]="c1.txt";
	char rout3[10]="i1.txt";
	char com[26]="main.exe <i1.txt >r1.txt";
	fstream out("result.txt",ios::out|ios::trunc);
	for(int i=1;i<10;i++)
	{
		rout1[1]=i+48;
		rout2[1]=i+48;
		rout3[1]=i+48;
		com[11]=i+48;
		com[19]=i+48;
		cout<<com<<endl;
		system(com) ;
		fstream r(rout1,ios::in);
		fstream t(rout2,ios::in);
		fstream infile(rout3,ios::in);
		if(!(r&&t)) 
		{
			cout<<"NEED FILE r"<<i<<".txt\n";
			break;
		}
		int m,n,t_x,t_y,temp,temp2;
		infile>>m>>n;
		for(int j=0;j<n;j++)
			for(int k=0;k<3;k++) infile>>temp;
		infile>>t_x>>t_y;
		out<<"--------------------------------test"<<i<<"-------------------------\n";
		t>>temp;
		if(temp==1) 
		{
			int flag=1;
			r>>temp;
			if(temp==1) out<<"Judge:\tRight\n";
			else out<<"Judge:\tWrong\n";
			if(m>1000) continue;
			for(int i=0;i<m*m;i++)
			{
				t>>temp;
				r>>temp2;
				if(temp!=temp2) 
				{
					flag=0;
					break;
				}
			}
			if(flag) out<<"Matrix:\tRight\n";
			else out<<"Matrix:\tWrong\n";
			flag=1;
			while(t>>temp)
			{
				r>>temp2;
				if(temp!=temp2) 
				{
					flag=0;
					break;
				}
			}
			if(flag) out<<"Rout:\tRight\n";
			else out<<"Rout:\tWrong\n";

		}
		else
		{
			r>>temp;
			if(temp==0) out<<"Judge:\tRight\n";
				else out<<"Judge:\tWrong\n";
		}		
		r.close();
		t.close();
		infile.close();
		out<<endl;
	}
	out<<"---------------------------------------------------------------";
	out.close();
	system("pause");
}
