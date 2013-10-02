#include<iostream>
using namespace std;
//Not confident about the struct of othrogonal list in textbook. There will be changes in code.
struct CrosLNode
{
	int row,col;
	double val;
	CrosLNode *down, *right;
};
struct CNode
{
	int row,col;
	CNode *next;
	CrosLNode *down, *right;
};
void CNode_init(CNode *t)
{
	int N=t[0].col;
	for(int i=1;i<N;i++) 
	{
		t[i].next=&t[i+1];
		t[i].col=0;
		t[i].row=0;
		t[i].right=NULL;
		t[i].down=NULL;
	}
	t[0].next=&t[1];
	t[N].next=NULL;
	t[N].col=0;
	t[N].row=0;
	t[N].right=NULL;
	t[N].down=NULL;
	return;
}
void print_matrix(CNode *t)
{
	CrosLNode *point;
	CNode *node_point;
	int N=t[0].col;
	for(int i=1;i<N+1;i++)
	{
		node_point=&t[i];
		point=(*node_point).right;
		while(point!=NULL)
		{
			cout<<(*point).row<<" "<<(*point).col<<" "<<(*point).val<<endl;
			point=(*point).right;
		}
	}
}
void build_list(CNode *t,CrosLNode *x,int m)
{
	int N=t[0].col;
	for(int i=0;i<m;i++)
	{
		int row=x[i].row,col=x[i].col;
		if(t[row+1].right==NULL) 
		{
			t[row+1].right=&x[i];
			x[i].right=NULL;
		}
		else 
		{
			CrosLNode *point=t[row+1].right;
			if((*point).col>col) 
			{
				x[i].right=point;
				t[row+1].right=&x[i];
			}
			else
				do
				{
					if((*(*point).right).col>col)  
					{
						x[i].right=(*point).right;
						(*point).right=&x[i];
						break;
					}
					if((*point).right==NULL&&col>(*point).col) 
					{
						(*point).right=&x[i];
						x[i].right=NULL;
						break;
					}
					point=(*point).right;
				}while((*point).right!=NULL);
		}
				
	}
	for(int i=0;i<m;i++)
	{
		int row=x[i].row,col=x[i].col;
		if(t[col+1].down==NULL) 
		{
			t[col+1].down=&x[i];
			x[i].down=NULL;
		}
		else 
		{
			CrosLNode *point=t[col+1].down;
			if((*point).row>row) 
			{
				x[i].down=point;
				t[col+1].down=&x[i];
			}
			else
				do
				{
					if((*(*point).down).row>row)  
					{
						x[i].down=(*point).down;
						(*point).down=&x[i];
						break;
					}
					if((*point).down==NULL&&row>(*point).row) 
					{
						(*point).down=&x[i];
						x[i].down=NULL;
						break;
					}
					point=(*point).down;
				}while((*point).down!=NULL);
		}
				
	}
}
int main()
{
	int N,m;
	cin>>N>>m;
	CNode *HEAD_A=new CNode[N+1];
	CNode *HEAD_B=new CNode[N+1];
	CNode *HEAD_C=new CNode[N+1];
	CrosLNode *Matrix_A=new CrosLNode[m];
	CrosLNode *Matrix_B=new CrosLNode[m];
	CrosLNode *Matrix_C=new CrosLNode[m];
	HEAD_A[0].col=N;
	HEAD_A[0].row=N;
	CNode_init(HEAD_A);
	/*
	HEAD_A[1].next=NULL;
	HEAD_A[1].right=&Matrix_A[0];
	HEAD_A[1].down=&Matrix_A[0];
	Matrix_A[0].col=1;
	Matrix_A[0].row=1;
	Matrix_A[0].val=10;
	Matrix_A[0].down=NULL;
	Matrix_A[0].right=NULL;
	print_matrix(HEAD_A);
	*/
	for(int i=0;i<m;i++)
	{
		cin>>Matrix_A[i].row>>Matrix_A[i].col>>Matrix_A[i].val;
		Matrix_A[i].right=NULL;
		Matrix_A[i].down=NULL;
	}
	build_list(HEAD_A,Matrix_A,m);
	print_matrix(HEAD_A);
	return 0;
}
	
	
			

