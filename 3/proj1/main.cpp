#include<iostream>
using namespace std;
static int m,n;
static int s_x,s_y,e_x,e_y;
struct data
{
	int x,y;
};
/*
class stack
{
public:
	stack(){};
	data pop();
	void push(int x,int y);
private:
	struct
	*/
void printmaze(char **maze,int m ,int n)
{
	for(int i=0;i<m;i++)
	{
		cout<<maze[i];
		cout<<endl;
	}
}
void delete_maze(char **maze,int m,int n)
{
	for(int i=0;i<m;i++) delete [](maze[i]);
	delete []maze;
}
void search(char **maze,char dir,int x,int y)
{
	if(x==e_x&&y==e_y) 
	{
		cout<<"Got it"<<endl;
		return ;
	}
	else if(maze[x-1][y]+maze[x+1][y]+maze[x][y+1]+maze[x][y-1]==195) return;
	else
	{
		switch(dir)
		{
			case 'u':
				if(maze[x-1][y]!='1') search(maze,'u',x-1,y);
				if(maze[x][y+1]!='1') search(maze,'r',x,y+1);
				if(maze[x][y-1]!='1') search(maze,'l',x,y-1);
				break;
			case 'r':
				if(maze[x][y+1]!='1') search(maze,'r',x,y+1);
				if(maze[x+1][y]!='1') search(maze,'d',x+1,y);
				if(maze[x-1][y]!='1') search(maze,'u',x-1,y);
				break;
			case 'l':
				if(maze[x][y-1]!='1') search(maze,'l',x,y-1);
				if(maze[x+1][y]!='1') search(maze,'d',x+1,y);
				if(maze[x-1][y]!='1') search(maze,'u',x-1,y);
				break;
			case 'd':
				if(maze[x+1][y]!='1') search(maze,'d',x+1,y);
				if(maze[x][y+1]!='1') search(maze,'r',x,y+1);
				if(maze[x][y-1]!='1') search(maze,'l',x,y-1);
				break;
			default:
				if(maze[x+1][y]!='1') search(maze,'d',x+1,y);
				if(maze[x-1][y]!='1') search(maze,'u',x-1,y);
				if(maze[x][y+1]!='1') search(maze,'r',x,y+1);
				if(maze[x][y-1]!='1') search(maze,'l',x,y-1);
				break;
		}
	}
}
int main()
{
	cin>>m>>n>>s_x>>s_y>>e_x>>e_y;
	char **maze=new char*[m];
	for(int i=0;i<m;i++)
	{
		maze[i]=new char[n+1];
		cin>>maze[i];
	}
	printmaze(maze,m,n);
	search(maze,0,s_x,s_y);
	delete_maze(maze,m,n);
}
