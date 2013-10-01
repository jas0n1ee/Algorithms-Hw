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
	}
	t[0].next=&t[1];
	t[N].next=&t[0];
	t[N].col=0;
	t[N].row=0;
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
int main()
{
	int N,m;
	cin>>N>>m;
	CNode *HEAD_A=new CNode[N+1];
	CrosLNode *Matrix_A=new CrosLNode[m];
	HEAD_A[0].col=N;
	HEAD_A[0].row=N;
	CNode_init(HEAD_A);
	HEAD_A[1].next=NULL;
	HEAD_A[1].right=&Matrix_A[0];
	HEAD_A[1].down=&Matrix_A[0];
	Matrix_A[0].col=1;
	Matrix_A[0].row=1;
	Matrix_A[0].val=10;
	Matrix_A[0].down=NULL;
	Matrix_A[0].right=NULL;
	print_matrix(HEAD_A);
	/*
	for(int i=0;i<m;i++)
	{
		
	*/
	return 0;
}
	
	
			

