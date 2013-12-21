#include<iostream>
using namespace std;
#define EMY_CHECK 'o'+'o'+'0'
#define MY_CHECK 'x'+'x'+'0'
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

int check(int &x,int &y)
{
	int emy=0;
	int my=0;
	int emy_x,emy_y,my_x,my_y;
	for(int i=0;i<3;i++)
	{
		int sum=0;
		if(sum_r(i)==EMY_CHECK) 
		{
			emy=1;
			for(int j=0;j<3;j++) if(board[i][j]==0) {emy_x=i; emy_y=j;}
		}
		if(sum_r(i)==MY_CHECK) 
		{
			my=1;
			for(int j=0;j<3;j++) if(board[i][j]==0) {my_x=i; my_y=j;}
		}
		if(sum_c(i)==EMY_CHECK) 
		{
			emy=1;
			for(int j=0;j<3;j++) if(board[j][i]==0) {emy_y=i; emy_x=j;}
		}
		if(sum_c(i)==MY_CHECK) 
		{
			my=1;
			for(int j=0;j<3;j++) if(board[j][i]==0) {my_y=i; my_x=j;}
		}
		if(sum_sl()==EMY_CHECK) 
		{
			emy=1;
			for(int j=0;j<3;j++) if(board[j][j]==0) {emy_x=emy_y=j;};
		}
		if(sum_sl()==MY_CHECK) 
		{
			my=1;
			for(int j=0;j<3;j++) if(board[j][j]==0) {my_x=my_y=j;};
		}
		if(sum_sr()==EMY_CHECK) 
		{
			emy=1;
			for(int j=0;j<3;j++) if(board[j][2-j]==0) {emy_x=j; emy_y=2-j;}
		}
		if(sum_sr()==MY_CHECK) 
		{
			my=1;
			for(int j=0;j<3;j++) if(board[j][2-j]==0) {my_x=j; my_y=2-j;}
		}
	}
	if(my) {x=my_x;y=my_y;}
	else if(emy) {x=emy_x;y=emy_y;}
	return emy+2*my;
}
void p_board()
{
	for(int i=0;i<3;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(board[i][j]!='0')
				cout<<(char)board[i][j]<<"\t";
			else cout<<" \t";
		}
		cout<<endl;
	}
}
int main(int argc,char*argv[])
{
	for(int i=0;i<9;i++) board[i/3][i%3]=*argv[i+1];
	p_board();
	int x,y;
	cout<<check(x,y);
}
