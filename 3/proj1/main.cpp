#include<iostream>
using namespace std;
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
int main()
{
	int m,n;
	int s_x,s_y,e_x,e_y;
	cin>>m>>n>>s_x>>s_y>>e_x>>e_y;
	char **maze=new char*[m];
	for(int i=0;i<m;i++)
	{
		maze[i]=new char[n+1];
		cin>>maze[i];
	}
	printmaze(maze,m,n);
	delete_maze(maze,m,n);
}
