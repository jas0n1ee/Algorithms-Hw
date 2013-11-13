#include<iostream>
#include<fstream>
#include<cmath>
#include<cstdlib>
#include<windows.h> 
using namespace std;
void get(char &t,fstream &in)
{
	if(!(t=in.get())) return;
	if(t==' ') get(t,in);
}
int main()
{
	SYSTEMTIME sys;
	int min,sec,ms;
	int count=0;
	char rout1[10]="a1_1.txt";
	char rout2[10]="o1_1.txt";
	char com[40]="main_1.exe i_1.txt o1_1.txt";
	fstream out("result.txt",ios::out|ios::trunc);
	for(int i=1;i<6;i++)
	{
		out<<"--------------------------test1_"<<i<<"----------------------------\n";
		rout1[3]=i+48;
		rout2[3]=i+48;
		com[13]=i+48;
		com[22]=i+48;
		min=sys.wMinute;
		sec=sys.wSecond;
		ms=sys.wMilliseconds;
		cout<<com<<endl; 
		system(com);
		//cout<<system(com); 
		//cout<<sys.wMinute<<sys.wSecond-sec<<sys.wMilliseconds-ms<<endl;
		fstream r(rout1,ios::in);
		fstream t(rout2,ios::in);
		if(!r) {cout<<"!!Lack file "<<rout1<<endl;continue;} 
		if(!t) {cout<<"!!Need file "<<rout2<<endl;continue;}
		//if(!(r&&t)) break;
		char t1,t2;
		bool flag=1;
		while(1)
		{
			get(t1,r);
			get(t2,t);
			if(t1!=t2) flag=0;
			if(t1=='\n'&&t2=='\n') break;
		}
		out<<"Keywords:\t";
		if(flag)out<<"Right\n";
		else out<<"Wrong\n";
		flag=1;
		r.get();t.get();
		while(1)
		{
			get(t1,r);
			get(t2,t);
			if(t1!=t2) flag=0;
			if(t1=='\n'&&t2=='\n') break;
		}
		out<<"Sum:\t\t";
		if(flag)out<<"Right\n";
		else out<<"Wrong\n";
		flag=1;
		int t3,t4;
		r>>t3;t>>t4;
		out<<"Level:\t\t";
		if(t3==t4) out<<"Right\n";
		else out<<"Wrong\n";
		r.close();
		t.close();
	}
	rout1[1]='2';
	rout2[1]='2';
	char com2[40]="main_2.exe p_1.txt c_1.txt o2_1.txt";
	for(int i=1;i<6;i++)
	{
		out<<"--------------------------test2_"<<i<<"----------------------------\n";
		rout1[3]=i+48;
		rout2[3]=i+48;
		com2[13]=i+48;
		com2[21]=i+48;
		com2[30]=i+48;
		cout<<com2<<endl;
		system(com2);
		//cout<<system(com); 
		//cout<<sys.wMinute<<sys.wSecond-sec<<sys.wMilliseconds-ms<<endl;
		fstream r(rout1,ios::in);
		fstream t(rout2,ios::in);
		if(!r) {cout<<"!!Need file "<<rout1<<endl;continue;} 
		if(!t) {cout<<"!!Need file "<<rout2<<endl;continue;}
		char temp[5],temp1[5];
		int x1,x2,n;
		if(r>>temp&&t>>temp1)
		{
			out<<"Result:\t\t";
			if(strcmp(temp,temp1)==0) out<<"Right\n";
			else out<<"Wrong\n";
			bool flag=1;
			if(temp[0]=='Y')
			{
				r>>x1;
				t>>x2;
				out<<"SUM:\t\t";
				if(x1!=x2)out<<"Wrong\n";
				else
				{
					out<<"Right\n";
					n=x1;
					for(int i=0;i<n;i++)
					{
						r>>x1;
						t>>x2;	
						if(x1!=x2) flag=0;
					}
				}
				out<<"Level:\t\t";
				if(flag) out<<"Right\n";
				else out<<"Wrong\n";
			}
		}
	}
	out<<"-------------------------------------------------------------\n";
	out.close();
	system("pause"); 
}
