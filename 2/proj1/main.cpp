#include<iostream>
using namespace std;
//Not confident about the struct of othrogonal list in textbook. There will be changes in code.
struct CrosLNode
{
	int row,col;
	int val;
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
void build_list(CNode *t,CrosLNode &x)
{
	int N=t[0].col;
	int row=x.row,col=x.col;
	CrosLNode *point=t[row+1].right;
	if(t[row+1].right==NULL||(*t[row+1].right).col>col)
	{
		x.right=t[row+1].right;
		t[row+1].right=&x;
	}
	else
	while(point!=NULL)
	{
		if((*point).right==NULL||(*(*point).right).col>col)
		{
			x.right=(*point).right;
			(*point).right=&x;
			break;
		}
		else point=(*point).right;
	}
	point=t[col+1].down;
	if(t[col+1].down==NULL||(*t[col+1].down).row>row)
	{
		x.down=t[col+1].down;
		t[col+1].down=&x;
	}
	else
	while(point!=NULL)
	{
		if((*point).down==NULL||(*(*point).down).row>row)
		{
			x.down=(*point).down;
			(*point).down=&x;
			break;
		}
		else point=(*point).down;
	}
}
CrosLNode * new_matrix(int row,int col,int val)
{
	CrosLNode *t=new CrosLNode;
	(*t).row=row;
	(*t).col=col;
	(*t).val=val;
	(*t).right=NULL;
	(*t).down=NULL;
	return t;
}
void delete_list(CNode *head)
{
	if((*head).right==NULL) return;
	else 
	{
		(*head).right=((*(*head).right)).right;
		delete (*head).right;
	}
	delete_list(head);
}
void delete_matrix(CNode *head)
{
	int N=head[0].col;
	CrosLNode *t=NULL;
	CrosLNode *d=NULL;
	for(int i=1;i<N+1;i++)
	{
		t=head[i].right;
		while(t!=NULL)
		{
			d=t;
			t=(*t).right;
			(*d).right=NULL;
			(*d).down=NULL;
			free( d);
		}
		head[i].right=NULL;
		//delete_list(head);
	}
	for(int i=1;i<N+1;i++) head[i].down=NULL;
}
void matrix_transpose(CNode *s,CNode *d)
{
	int N=s[0].col;
	CrosLNode *point=NULL;
	for(int i=1;i<N+1;i++) 
	{
		point=s[i].right;
		while(point!=NULL)
		{
			build_list(d,*new_matrix((*point).col,(*point).row,(*point).val));
			point=(*point).right;
		}
	}
}
void matrix_add(CNode *A, CNode *B, CNode *C)
{
	int N=A[0].col;
	for(int i=1;i<N+1;i++)
	{
		int *t=new int[N];
		for(int j=0;j<N;j++) t[j]=0;
		CrosLNode *point=A[i].right;
		while(point!=NULL)
		{
			t[(*point).col]+=(*point).val;
			point=(*point).right;
		}
		point=B[i].right;
		while(point!=NULL)
		{
			t[(*point).col]+=(*point).val;
			point=(*point).right;
		}	
		for(int j=0;j<N;j++)
		{
			if(t[j]!=0) build_list(C,*new_matrix(i-1,j,t[j]));
		}
		delete []t;
	}
}
void matrix_dot(CNode *A,CNode*B,CNode *C)
{
	int N=A[0].col;
	CrosLNode *row;
	CrosLNode *col;
	for(int i=1;i<N+1;i++)
	{
		for(int j=1;j<N+1;j++)
		{
			int t=0;
			row=A[i].right;
			while(row!=NULL)
			{
				col=B[j].down;
				while(col!=NULL)
				{
					if ((*row).col==(*col).row)
					{
						t+=(*row).val*(*col).val;
						break;
					}
					else col=(*col).down;
				}
				row=(*row).right;
			}
			if(t!=0) build_list(C,*new_matrix(i-1,j-1,t));
		}
	}
}
void print_full_matrix(CNode *t)
{
	int N=(*t).col;
	CrosLNode *point;
	for(int i=1;i<N+1;i++)
	{
		point=t[i].right;
		int r=-1;
		while(point != NULL)
		{
			for(int j=0;j<(*point).col-r-1;j++) cout<<"0 ";
			cout<<(*point).val<<" ";
			r=(*point).col;
			point=(*point).right;
		}
		cout<<endl;
	}
}
int main()
{
	int N,m;
	cin>>N>>N>>m;
	CNode *HEAD_A=new CNode[N+1];
	CNode *HEAD_B=new CNode[N+1];
	CNode *HEAD_C=new CNode[N+1];
	CNode *HEAD_D=new CNode[N+1];
	CrosLNode *Matrix_A=new CrosLNode[m];
	CrosLNode *Matrix_B=new CrosLNode[m];
	HEAD_A[0].col=N;
	HEAD_A[0].row=N;
	HEAD_B[0].col=N;
	HEAD_B[0].row=N;
	HEAD_C[0].col=N;
	HEAD_C[0].row=N;
	HEAD_D[0].row=N;
	HEAD_D[0].col=N;
	CNode_init(HEAD_A);
	CNode_init(HEAD_B);
	CNode_init(HEAD_C);
	CNode_init(HEAD_D);
	for(int i=0;i<m;i++)
	{
		cin>>Matrix_A[i].row>>Matrix_A[i].col>>Matrix_A[i].val;
		Matrix_A[i].right=NULL;
		Matrix_A[i].down=NULL;
		build_list(HEAD_A,Matrix_A[i]);
	}
	matrix_transpose(HEAD_A,HEAD_B);
	print_matrix(HEAD_B);
	matrix_add(HEAD_A,HEAD_B,HEAD_C);
	print_matrix(HEAD_C);
	matrix_dot(HEAD_A,HEAD_B,HEAD_D);
	print_matrix(HEAD_D);
//	delete_matrix(HEAD_A);
//	delete_matrix(HEAD_B);
	delete [] HEAD_A;
	delete [] HEAD_B;
	return 0;
}
	
	
			

