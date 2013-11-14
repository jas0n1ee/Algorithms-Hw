#include<iostream>
using namespace std;
static int m,n;
int *DFN,*STACK,*Low,*visit,*instack;
int index=-1;
int top=-1;
int cnt=0;
struct node
{
	int index;
	int lowlink;
};
int min(int x,int y)
{
	if(x==0||x>y) return y;
	else return x;
}
void tarjan(int **matrix,int u)
{
	int v;
	DFN[u]=Low[u]=++index;
	instack[u]=1;
	STACK[++top]=u;
	if(top>=m+1) cerr<<"ERROR!!!!!";
	for(int i=0;i<m;i++)
	{
		if(matrix[u][i]!=0)
		{
			if(!DFN[i])
			{
				tarjan(matrix,i);
				Low[u]=(Low[u]>Low[i])?Low[i]:Low[u];
			}
			else if(instack[u])
				Low[u]=(Low[u]>Low[i])?Low[i]:Low[u];
		}
	}
	if (DFN[u] == Low[u])
	do
	{
		v=STACK[top--];
		instack[v]=0;
	}while(u!=v);
	cnt++;	
	
}
bool s_connect(int **matrix)
{
	if(n<m) return 0;
	else 
	{
		DFN = new int[m+2];
		Low = new int[m+2];
		STACK = new int[m+2];
		instack = new int[m+2];
		for (int i=0; i<m; i++)
		{
			DFN[i] = 0;
			Low[i] = 0;
			STACK[i] = 0;
			instack[i] = false;
		}
		top = 0;
		cnt = 0;
		index = 0;
		for (int i = 0; i<m; i++)
		{
			if (!DFN[i])
				tarjan(matrix,i);
		}
		delete []DFN;
		delete []Low;
		delete []instack;
		delete []STACK;
		if (cnt) return 1;
		else return 0;
	}
}
void floyd(int **matrix)
{
	for(int k=0;k<m;k++)
	{
		for(int i=0;i<m;i++)
		{
			for(int j=0;j<m;j++)
			{
				if(i==j) continue;
				if(k==i||k==j) continue;
				if(matrix[i][k]==0||matrix[k][j]==0) continue;
				matrix[i][j]=min(matrix[i][j],matrix[i][k]+matrix[k][j]);
				//matrix[j][i]=min(matrix[j][i],matrix[j][k]+matrix[k][i]);
			}
		}
	}
}
void short_rout(int **matrix,int **original,int x,int y)
{
	if(matrix[x][y]==original[x][y])
	{
		cout<<x<<" ";
		return;
	}
	else
	{
		for(int i=0;i<m;i++)
		{
			if(i==x||i==y) continue;
			if(matrix[x][i]+matrix[i][y]==matrix[x][y]) 
			{
				short_rout(matrix,original,x,i);
				short_rout(matrix,original,i,y);
				break;
			}
		}
	}
}
int main()
{
	int tar_x,tar_y;
	cin>>m>>n;
	int **matrix,**back;
	matrix=new int*[m];
	back=new int*[m];
	for(int i=0;i<m;i++)
	{
		matrix[i]=new int[m];
		back[i]=new int[m];
		for(int j=0;j<m;j++)
		{
			matrix[i][j]=0;
			back[i][j]=0;
		}
	}
	for(int i=0;i<n;i++) 
	{
		int t[3];
		cin>>t[0]>>t[1]>>t[2];
		matrix[t[0]][t[1]]=t[2];
		back[t[0]][t[1]]=t[2];
	}
	cin>>tar_x>>tar_y;
	switch(m>1000)
	{
		case 0:
			if(s_connect(matrix))
			{
				cout<<"1\n\n";
				floyd(matrix);
				for(int i=0;i<m;i++)
				{
					for(int j=0;j<m;j++) cout<<matrix[i][j]<<" ";
					cout<<endl;
				}
				cout<<endl;
				short_rout(matrix,back,tar_x,tar_y);
				cout<<tar_y;
			}
			else cout<<"0\n";
			break;
		case 1:
			if(s_connect(matrix))
			{
				cout<<"1\n";
			}
			else cout<<"0\n";
			break;
	}
	return 0;
}
