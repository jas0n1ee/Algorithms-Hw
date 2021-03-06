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
	CrosLNode *down_last,*right_last;
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
		t[i].down_last=NULL;
		t[i].right_last=NULL;
	}
	t[0].next=&t[1];
	t[N].next=NULL;
	t[N].col=0;
	t[N].row=0;
	t[N].right=NULL;
	t[N].down=NULL;
	t[N].down_last=NULL;
	t[N].right_last=NULL;
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
void quick_insert(CNode *t,CrosLNode &x)
{
	int N=t[0].col;
	int row=x.row,col=x.col;
	if(t[row+1].right_last==NULL) 
	{
		t[row+1].right=&x;
		t[row+1].right_last=&x;
		x.right=NULL;
	}
	else 
	{
		(*t[row+1].right_last).right=&x;
		t[row+1].right_last=&x;
		x.right=NULL;
	}

	if(t[col+1].down_last==NULL) 
	{
		t[col+1].down=&x;
		t[col+1].down_last=&x;
		x.down=NULL;
		}
	else 
	{
		(*t[col+1].down_last).down=&x;
		t[col+1].down_last=&x;
		x.down=NULL;
	}
}
CrosLNode * new_matrix(int row,int col,int val)
{
	CrosLNode *t=new CrosLNode();
	(*t).row=row;
	(*t).col=col;
	(*t).val=val;
	(*t).right=NULL;
	(*t).down=NULL;
	return t;
}
void del_matrix(CNode *head)
{
	int N=head[0].col;
	for(int i=1;i<N+1;i++) head[i].down=NULL;
	CrosLNode *t=NULL;
	for(int i=1;i<N+1;i++)
	{
		while(head[i].right!=NULL)
		{
			t=head[i].right;
			head[i].right=(*t).right ;
			delete t;
			
		}
		head[i].right=NULL;
	}
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
			quick_insert(d,*new_matrix((*point).col,(*point).row,(*point).val));
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
			if(t!=0) quick_insert(C,*new_matrix(i-1,j-1,t));
		}
	}
}
void matrix_quick_dot(CNode *A,CNode *B,CNode *C)
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
			col=B[j].down;
			while(row!=NULL&&col!=NULL)
			{
				
				if((*row).col>(*col).row)
				{
					col=(*col).down;
					continue;
				}
				if((*row).col<(*col).row) 
				{
					row=(*row).right;
					continue;
				}
				if((*row).col==(*col).row) 
				{
					t+=(*row).val*(*col).val;
					row=(*row).right;
					col=(*col).down;
				}
			}
			if(t!=0) quick_insert(C,*new_matrix(i-1,j-1,t));
		}
	}
}
void matrix_add_quick(CNode *A,CNode *B,CNode *C)
{
	int N=A[0].col;
	CrosLNode *row;
	CrosLNode *row2;
	for(int i=1;i<N+1;i++)
	{
		row=A[i].right;
		row2=B[i].right;	
		while(row!=NULL||row2!=NULL)
		{
			if(row==NULL&&row2!=NULL)
			{
				quick_insert(C,*new_matrix(i-1,(*row2).col,(*row2).val));
				row2=(*row2).right;
				continue;
			}
			if(row2==NULL&&row!=NULL)
			{
				quick_insert(C,*new_matrix(i-1,(*row).col,(*row).val));
				row=(*row).right;
				continue;
			}
			if((*row).col>(*row2).col) 
			{
				quick_insert(C,*new_matrix(i-1,(*row2).col,(*row2).val));
				row2=(*row2).right;
				continue;
			}
			if((*row).col<(*row2).col) 
			{
				quick_insert(C,*new_matrix(i-1,(*row).col,(*row).val));
				row=(*row).right;
				continue;
			}
			if((*row).col==(*row2).col) 
			{
				if(((*row).val+(*row2).col)!=0)
				{
					quick_insert(C,*new_matrix(i-1,(*row).col,(*row).val+(*row2).val));
					row=(*row).right;
					row2=(*row2).right;
				}
				else
				{
					row=(*row).right;
					row2=(*row2).right;
				}
			}
		}
	}
	
}
void matrix_fast_add(CNode *A,CNode *B,CNode *C)
{
	int N=A[0].col;
	CrosLNode *row;
	CrosLNode *row2;
	int flag=0;
	for(int i=1;i<N+1;i++)
	{
		row=A[i].right;
		while(row!=NULL)
		{
			row2=B[i].right;
			flag=0;
			while(row2!=NULL)
			{
				if ((*row).col==(*row2).col)
				{
					if(((*row).val+(*row2).val)!=0) quick_insert(C,*new_matrix(i-1,(*row).col,(*row).val+(*row2).val));
					flag=1;
					break;
				}
				else row2=(*row2).right;
			}
			if(flag==0) quick_insert(C,*new_matrix(i-1,(*row).col,(*row).val));
			row=(*row).right;
		}
	}
	for(int i=1;i<N+1;i++)
	{
		row=B[i].right;
		while(row!=NULL)
		{
			row2=A[i].right;
			flag=0;
			while(row2!=NULL)
			{
				if ((*row).col==(*row2).col)
				{
					flag=1;
					break;
				}
				else row2=(*row2).right;
			}
			if(flag==0) build_list(C,*new_matrix(i-1,(*row).col,(*row).val));
			row=(*row).right;
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
		build_list(HEAD_A,*new_matrix(Matrix_A[i].row,Matrix_A[i].col,Matrix_A[i].val));
	}
	matrix_transpose(HEAD_A,HEAD_B);
	print_matrix(HEAD_B);
	matrix_add_quick(HEAD_A,HEAD_B,HEAD_C);
	print_matrix(HEAD_C);
	matrix_quick_dot(HEAD_A,HEAD_B,HEAD_D);
	print_matrix(HEAD_D);
	del_matrix(HEAD_A);
	del_matrix(HEAD_B);
	del_matrix(HEAD_C);
	del_matrix(HEAD_D);
	delete [] HEAD_A;
	delete [] HEAD_B;
	delete [] HEAD_C;
	delete [] HEAD_D;
	return 0;
}
	
	
			

