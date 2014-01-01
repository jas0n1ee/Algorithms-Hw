#include<iostream>
using namespace std;
#define EMY_CHECK 'o'+'o'
#define MY_CHECK 'x'+'x'
#define init_board  0
#define full_board 'o'+'x'+'o'+'x'+'o'+'x'+'o'+'x'+'x'
int board[3][3];
float rate=0;
float my(int l);
float emy(int l);
int sum_r(int x)
{
	return board[x][0]+board[x][1]+board[x][2];
}
int sum_c(int x)
{
	return board[0][x]+board[1][x]+board[2][x];
}
int sum_sl()
{
	return board[0][0]+board[1][1]+board[2][2];
}
int sum_sr()
{
	return board[0][2]+board[1][1]+board[2][0];
}

int sum_total()
{
	int sum=0;
	for(int i=0;i<9;i++) sum+=board[i/3][i%3];
	return sum;
}
float gg()
{
	int result=0;
	int sum;
	for(int i=0;i<3;i++)
	{
		sum=sum_r(i);
		if(sum==3*'x') return 1;
		if(sum==3*'o') return 0;
		sum=sum_c(i);
		if(sum==3*'x') return 1;
		if(sum==3*'o') return 0;
	}
	sum=sum_sr();
	if(sum==3*'x') return 1;
	if(sum==3*'o') return 0;
	sum=sum_sl();
	if(sum==3*'x') return 1;
	if(sum==3*'o') return 0;
	if(sum_total()==full_board) return rate;
	else return -1;
}
int check(int *x,int *y)
{
	int emy=0;
	int my=0;
	int emy_x,emy_y,my_x,my_y;
	int sum_e=0,sum_m=0;
	for(int i=0;i<3;i++)
	{
		if(sum_r(i)==EMY_CHECK) 
		{
			emy=1;
			for(int j=0;j<3;j++) if(board[i][j]==0) {emy_x=i; emy_y=j;sum_e++;}
		}
		if(sum_r(i)==MY_CHECK) 
		{
			my=1;
			for(int j=0;j<3;j++) if(board[i][j]==0) {my_x=i; my_y=j;sum_m++;}
		}
		if(sum_c(i)==EMY_CHECK) 
		{
			emy=1;
			for(int j=0;j<3;j++) if(board[j][i]==0) {emy_y=i; emy_x=j;sum_e++;}
		}
		if(sum_c(i)==MY_CHECK) 
		{
			my=1;
			for(int j=0;j<3;j++) if(board[j][i]==0) {my_y=i; my_x=j;sum_m++;}
		}
	}
	if(sum_sl()==EMY_CHECK) 
	{
		emy=1;
		for(int j=0;j<3;j++) if(board[j][j]==0) {emy_x=j; emy_y=j;sum_e++;}
	}
	if(sum_sl()==MY_CHECK) 
	{
		my=1;
		for(int j=0;j<3;j++) if(board[j][j]==0) {my_x=j; my_y=j;sum_m++;}
	}
	if(sum_sr()==EMY_CHECK) 
	{
		emy=1;
		for(int j=0;j<3;j++) if(board[j][2-j]==0) {emy_x=j; emy_y=2-j;sum_e++;}
	}
	if(sum_sr()==MY_CHECK) 
	{
		my=1;
		for(int j=0;j<3;j++) if(board[j][2-j]==0) {my_x=j; my_y=2-j;sum_m++;}
	}
	
	if(my) {*x=my_x;*y=my_y;}
	else if(emy) {*x=emy_x;*y=emy_y;}
	if(!sum_e>=2) return 11;
	else return emy+2*my;
}
void p_board()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]!=0)
				cout<<(char)board[i][j]<<" ";
			else cout<<"M ";
		}
		cout<<endl;
	}
}
float my(int l)
{
	board[l/3][l%3]='x';
	float r=gg();
	if(r!=-1) 
	{
		board[l/3][l%3]=0;
		return r;
	}
	else
	{
		r=0;
		for(int i=0;i<9;i++)
		{
			if(board[i/3][i%3]==0)
			{
				r+=emy(i);
			}
		}
		board[l/3][l%3]=0;
		return r;
	}

}
float emy(int l)
{
	board[l/3][l%3]='o';
	float r=gg();
	if(r!=-1) 
	{
		board[l/3][l%3]=0;
		return r;
	}
	else
	{
		r=0;
		for(int i=0;i<9;i++)
		{
			if(board[i/3][i%3]==0)
			{
				r+=my(i);
			}
		}
		board[l/3][l%3]=0;
		return r;
	}
}
int strategy()
{
	float r[9]={0};
	float max=-1;
	for(int i=0;i<9;i++)
	{
		if(board[i/3][i%3]==0)
		{
			r[i]=my(i);
			if(r[i]>max) max=r[i];
		}
	}
	for(int i=0;i<9;i++) 
	{
		if(r[i]==max) 
		{
			return i;
		}
	}
}
int main(int argc,char*argv[])
{
	for(int i=0;i<9;i++) 
	{
		if(*argv[i+1]=='0') board[i/3][i%3]=0;
		else board[i/3][i%3]=*argv[i+1];
	}
	rate=argv[10][0]*1+argv[10][2]*0.1+argv[10][3]*0.01-'0'*1.11;
	cout<<strategy()+1<<endl;
}
