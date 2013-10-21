#include<iostream>
using namespace std;
static int m,n;
static int s_x,s_y,e_x,e_y;
static int minlen=2141483647;
void printmaze(int **maze)
{
	for(int i=0;i<m;i++)
	{
		for(int j=0;j<n;j++)cout<<maze[i][j];
		cout<<endl;
	}
}
void delete_maze(int **maze,int m,int n)
{
	for(int i=0;i<m;i++) delete [](maze[i]);
	delete []maze;
}
void mark(int **maze,int x,int y)
{
	if(x==e_x&&y==e_y) 
	{
		minlen=maze[x][y];
		return;
	}
	if(maze[x][y]>minlen) return;
	if((maze[x+1][y]==1||maze[x+1][y]<=maze[x][y]+1)&&maze[x+1][y]!=0) ;
	else 
	{
		maze[x+1][y]=maze[x][y]+1;
		mark(maze,x+1,y);
	}
	if((maze[x-1][y]==1||maze[x-1][y]<=maze[x][y]+1)&&maze[x-1][y]!=0);
	else 
	{
		maze[x-1][y]=maze[x][y]+1;
		mark(maze,x-1,y);
	}
	if((maze[x][y+1]==1||maze[x][y+1]<=maze[x][y]+1)&&maze[x][y+1]!=0);
	else 
	{
		maze[x][y+1]=maze[x][y]+1;
		mark(maze,x,y+1);
	}
	if((maze[x][y-1]==1||maze[x][y-1]<=maze[x][y]+1)&&maze[x][y-1]) ;
	else 
	{
		maze[x][y-1]=maze[x][y]+1;
		mark(maze,x,y-1);
	}
}
void routit(int **maze,int x,int y,int *rx,int *ry)
{
	int N=maze[x][y];
	rx[N-2]=x;
	ry[N-2]=y;
	if(x==s_x&&y==s_y) return;
	else
	{
		if(maze[x-1][y]==N-1) routit(maze,x-1,y,rx,ry);
		if(maze[x+1][y]==N-1) routit(maze,x+1,y,rx,ry);
		if(maze[x][y+1]==N-1) routit(maze,x,y+1,rx,ry);
		if(maze[x][y-1]==N-1) routit(maze,x,y-1,rx,ry);
	}
}
		


int main()
{
	cin>>m>>n>>s_x>>s_y>>e_x>>e_y;
	int **maze=new int*[m];
	cin.get(); 
	for(int i=0;i<m;i++)
	{
		maze[i]=new int[n];
		for(int j=0;j<n;j++) maze[i][j]=cin.get()-48;
		cin.get();
	}
	maze[s_x][s_y]=2;
	mark(maze,s_x,s_y);
	int *rx=new int[minlen-1];
	int *ry=new int[minlen-1];
	routit(maze,e_x,e_y,rx,ry);
	for(int i=0;i<minlen-1;i++)
	{
		cout<<rx[i]<<" "<<ry[i]<<endl;
	}
	delete_maze(maze,m,n);
	delete []rx;
	delete []ry;
}
