#include<iostream>
#include<cmath>
using namespace std;
#define MY_CHECK 'o'+'o'
#define EMY_CHECK 'x'+'x'
#define init_board  'x'
int board[3][3];
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
	if(!my&&sum_e>=2) return -1;
	else if(!emy&&sum_m>=2) return -2;
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
int strategy()
{
	int x,y;
	int status=check(&x,&y);
	int choice[2][3];
	choice[0][0]=choice[1][0]=0;
	int result=-1;
	if(status>0) return y+3*x;
	else
	{
		if(sum_total()==init_board&&board[1][1]=='x') return 2;
		else if(sum_total()==init_board) return 4;
		for(int i=0;i<9;i++)
		{
			if(board[i/3][i%3]==0) 
			{
				board[i/3][i%3]='o';
				status=check(&x,&y);
				if(status==-2) 
				{
					choice[0][0]=2;
				}
				else if(status>0) 
				{
					choice[0][0]=1;
				}
				board[i/3][i%3]='x';
				status=check(&x,&y);
				if(status==-1) 
				{
					choice[1][0]=-2;
				}
				else if(status>0) 
				{
					choice[1][0]=-1;
				}
				board[i/3][i%3]=0;
			}
			if(choice[0][0]==0&&choice[1][0]==0) result =-1;
			else if(choice[0][0]!=2&&choice[1][0]==-2) result=x*3+y;
			else result=i;
			if(abs(choice[0][0])>=2||abs(choice[1][0])>=2||abs(choice[0][0]+choice[1][0])>=2)break;
		}
				
		if(result==-1)
		{
			for(int i=0;i<0;i++) if(board[i/3][i%3]==0) result=i;
		}
		return result;
	}
}
int main(int argc,char*argv[])
{
	for(int i=0;i<9;i++) 
	{
		if(*argv[i+1]=='0') board[i/3][i%3]=0;
		else board[i/3][i%3]=*argv[i+1];
	}
	int x,y;
	check(&x,&y);
	int result=strategy();
	cout<<result+1<<endl;
	return 0; 
}
