#include<iostream>
using namespace std;
static int m,n;
static int s_x,s_y,e_x,e_y;
static int minlen=2141483647;
struct data
{
	int x,y;
	data(){};
	data(int a,int b):x(a),y(b){}
};
struct LNode
{
	struct data data;
	LNode* next;
};
 struct Stack
 { 
	LNode* top;    
	int length;  
 };
 void InitStack ( Stack &S )
 { 
	S.top = NULL;  
	S.length = 0;  
 } 
 void Push ( Stack &S, data e )
 {
	LNode *p = new LNode;   
	if(!p) return;  
	p -> data = e;
	p -> next = S.top; 
	S.top=p;    
	++S.length;   
 } 
 bool Pop (Stack &S,data &temp)
 { 
   if ( !S.top )
   {
	   return false; 
   }
   else 
   {
		temp= S.top -> data;   
		LNode *q = S.top; 
		S.top = S.top -> next;  
		--S.length;    
		delete q;       
		return true;
     }
 }
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
void mark(int **maze,Stack &s,int x,int y)
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
		Push(s,data(x+1,y));
	}
	if((maze[x-1][y]==1||maze[x-1][y]<=maze[x][y]+1)&&maze[x-1][y]!=0);
	else 
	{
		maze[x-1][y]=maze[x][y]+1;
		Push(s,data(x-1,y));
	}
	if((maze[x][y+1]==1||maze[x][y+1]<=maze[x][y]+1)&&maze[x][y+1]!=0);
	else 
	{
		maze[x][y+1]=maze[x][y]+1;
		Push(s,data(x,y+1));
	}
	if((maze[x][y-1]==1||maze[x][y-1]<=maze[x][y]+1)&&maze[x][y-1]) ;
	else 
	{
		maze[x][y-1]=maze[x][y]+1;
		Push(s,data(x,y-1));
	}




	if(x<e_x&&maze[x+1][y]!=1&&(maze[x+1][y]==0||maze[x+1][y]>maze[x][y]))
	{
		maze[x+1][y]=maze[x][y]+1;
		Push(s,data(x+1,y));
	}
	else if(y<e_y&&maze[x][y+1]!=1&&(maze[x][y+1]==0||maze[x][y+1]>maze[x][y]))
	{
		maze[x][y+1]=maze[x][y]+1;
		Push(s,data(x,y+1));
	}
	else if(x>e_x&&maze[x-1][y]!=1&&(maze[x-1][y]==0||maze[x-1][y]>maze[x][y]))
	{
		maze[x-1][y]=maze[x][y]+1;
		Push(s,data(x-1,y));
	}
	else if(y>e_y&&maze[x][y-1]!=1&&(maze[x][y-1]==0||maze[x][y-1]>maze[x][y]))
	{
		maze[x][y-1]=maze[x][y]+1;
		Push(s,data(x,y-1));
	}
}
data routit(int **maze,int x,int y,int *rx,int *ry)
{
	int N=maze[x][y];
	rx[N-2]=x;
	ry[N-2]=y;
	if(x==s_x&&y==s_y) return data(-1,-1);
	else
	{
		if(maze[x-1][y]==N-1) return data(x-1,y);
		else if(maze[x+1][y]==N-1) return data(x+1,y);
		else if(maze[x][y+1]==N-1) return data(x,y+1);
		else if(maze[x][y-1]==N-1) return data(x,y-1);
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
	Stack s;
	InitStack(s);
	Push(s,data(s_x,s_y));
	maze[s_x][s_y]=2;
	data temp;
	while(Pop(s,temp))
	{
		mark(maze,s,temp.x,temp.y);
		if(temp.x==e_x&&temp.y==e_y) break; 
	}
	int *rx=new int[minlen-1];
	int *ry=new int[minlen-1];
	while(1)
	{
		data t;
		if(e_x==-1&&e_y==-1) break;
		else 
		{
			t=routit(maze,e_x,e_y,rx,ry);
			e_x=t.x;
			e_y=t.y;
		}
	}
	for(int i=0;i<minlen-1;i++)
	{
		cout<<rx[i]<<" "<<ry[i]<<endl;
	}
	delete_maze(maze,m,n);
	delete []rx;
	delete []ry;
}
