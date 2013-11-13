#include<iostream>
using namespace std;
static int m,n;
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
bool s_connect(int **maze)
{
	if(n<m) return 0;
	else return 1;
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
				cout<<"1\n";
				floyd(matrix);
				for(int i=0;i<m;i++)
				{
					for(int j=0;j<m;j++) cout<<matrix[i][j]<<" ";
					cout<<endl;
				}
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
