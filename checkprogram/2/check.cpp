#include<iostream>
#include<fstream>
#include<cmath>
using namespace std;
int main()
{
	int count=0;
	char rout1[10]="r1.txt";
	char rout2[10]="t1.txt";
	fstream out("result.txt",ios::out|ios::trunc);
	int b[6];
	fstream in("short.txt",ios::in);
	int i=1;
	while(in>>b[i]){i++;};
	for(int i=1;i<6;i++)
	{
		rout1[1]=i+48;
		rout2[1]=i+48;
		fstream r(rout1,ios::in);
		fstream t(rout2,ios::in);
		if(!(r&&t)) break;
		int m,n,s_x,s_y,e_x,e_y;
		t>>m>>n>>s_x>>s_y>>e_x>>e_y;
		int **temp=new int*[m];
		t.get(); 
		for(int j=0;j<m;j++)
		{
			temp[j]=new int[n];
			for(int k=0;k<n;k++) temp[j][k]=t.get();
			t.get();
		}
		//read the maze from t1 
		bool flag=0,flag1=0;
		int x,y,ex,ey;	
		int count =1;
		if(r>>x&&r>>y) 
		{
			if(x==s_x&&y==s_y) out<<i<<": Start Point Correct\n";
			else  out<<i<<": Start Point Wrong\n";
		}
		else out<<i<<": File Wrong\n";
		ex=x;ey=y;
		while(!r.eof())	
		{
			if(r>>x&&r>>y)
			{
				if((abs(ex-x)+abs(ey-y))!=1) flag=1;
				if(temp[x][y]==49) flag1=1;
				count++;
			}
			ex=x;ey=y;
		}
		if(flag1) out<<i<<": Data Wrong\n";
		else	 out<<i<<": Data Correct\n";
		if(flag) out<<i<<": Route Wrong\n";
		else	 out<<i<<": Route Correct\n";
		if(ex==e_x&&ey==e_y) out<<i<<": Stop Point Correct\n";
		else  out<<i<<": Stop Point Wrong\n";
		out<<i<<": "<<count-b[i]<<" steps \n";

		for(int j=0;j<m;j++) delete [](temp[j]);
		delete []temp;
		r.close();
		t.close();
		out<<endl;
	}
	out.close();
}
