#include<iostream>
#include<fstream>
using namespace std;
static int s_max=0,stage=0;
static int i=-1;
struct binode
{
	int data;
	int sum;
	binode *lchild,*rchild;
};
void init(int data,binode *t)
{
	t->data=data;
	t->sum=1;
	t->lchild=NULL;
	t->rchild=NULL;
}
void addchild(binode *t,int data)
{
	t->sum++;
	stage++;
	if(data < t->data)
	{
		if(t->lchild==NULL)
		{
			t->lchild=new binode;
			t->lchild->data=data;
			t->lchild->lchild=NULL;
			t->lchild->rchild=NULL;
			t->lchild->sum=1;
		}
		else addchild(t->lchild,data);
	}
	else
	{
		if(t->rchild==NULL)
		{
			t->rchild=new binode;
			t->rchild->data=data;
			t->rchild->lchild=NULL;
			t->rchild->rchild=NULL;
			t->rchild->sum=1;
		}
		else addchild(t->rchild,data);
	}
}
void delete_tree(binode *t)
{
	if(t==NULL)return;
	if(t->lchild!=NULL) delete_tree(t->lchild);
	if(t->rchild!=NULL) delete_tree(t->rchild);
	delete t;
}
void outbitree(binode *t,fstream &out)
{
	if(t==NULL) out<<"# ";
	else
	{
		out<<t->sum<<" ";
		outbitree(t->lchild,out);
		outbitree(t->rchild,out);
	}
}
void mark(binode *t, int *l)
{
	if(t==NULL) return;
	i++;
	if(t->lchild==NULL&&t->rchild==NULL)
	{
		l[i]=0;
		return;
	}
	else if(t->lchild!=NULL&&t->rchild==NULL)
	{
		l[i]=1;
		mark(t->lchild,l);
	}
	else if(t->lchild==NULL&&t->rchild!=NULL)
	{
		l[i]=2;
		mark(t->rchild,l);
	}
	else
	{
		l[i]=3;
		mark(t->lchild,l);
		mark(t->rchild,l);
	}
}
void Next(int *p,int *n,int m)
{
	n[0]=0;
	int i=1,j=0;
	while(i<m)
	{
		if(p[i]==p[j])
		{
			n[i]=j+1;
			i++;
			j++;
		}
		else if(j>0) j=n[j-1];
		else
		{
			n[i++]=0;
		}
	}
}
int kmp_match(int *t,int *p,int m,int n,int *r)
{
	int i=0,j=0,k=0;
	int *nxt=new int [n];
	Next(p,nxt,n);
	while(i<m)
	{
		if(t[i]==p[j])
		{
			if(j==n-1) 
			{
				r[k]=i-j;
				k++;
				i++;
				j=0;
			}
			else
			{
				i++;j++;
			}
		}
		else
		{
			if(j>0) j=nxt[j-1];
			else i++;
		}
	}
	delete [] nxt;
	return k;
}
void magic(binode *t,int * match,int k)
{
	if(i==k) return;
	s_max++;
	if(match[i]==s_max)
	{
		match[i]=stage;
		i++;
	}
	stage++;
	if(t->lchild!=NULL) magic(t->lchild,match,k);
	if(t->rchild!=NULL) magic(t->rchild,match,k);
	stage--;
}
void swap(int &x,int &y)
{
	int t=x;
	x=y;
	y=t;
}
void bubble(int *match,int k)
{
	int flag=1;
	for(int j=0;j<k;j++)
	{
		flag=1;
		for(int m=0;m<k-1;m++)
		{
			if(match[m]>match[m+1])
			{
				flag =0;
				swap(match[m],match[m+1]);
			}
		}
		if(flag) break;
	}
}

int main(int argc,char *argv[])
{
	fstream in1(argv[1],ios::in);
	fstream in2(argv[2],ios::in);
	fstream out(argv[3],ios::out|ios::trunc);
	binode *p=new binode;
	binode *c=new binode;
	int temp;
	int *match;
	if(in1>>temp) init(temp,p);
	else cerr<<"error";
	while(in1>>temp)
	{
		stage=1;
		addchild(p,temp);
		if(stage>s_max) s_max=stage;
	}
	int *par=new int[p->sum];

	s_max=0;
	if(in2>>temp) init(temp,c);
	else cerr<<"error";
	while(in2>>temp)
	{
		stage=1;
		addchild(c,temp);
		if(stage>s_max) s_max=stage;
	}
	int *child=new int[c->sum];
	match = new int[p->sum];
	mark(p,par);
	i=-1;
	mark(c,child);
	int k=kmp_match(par,child,p->sum,c->sum,match);
	if(k) 
	{
		s_max=-1;
		i=0;
		stage=1;
		magic(p,match,k);
		bubble(match,k);
		out<<"YES\n";
		out<<k<<endl;
		for(int j=0;j<k;j++) out<<match[j]<<endl;
	}
	else out<<"NO";
	delete [] match;
	delete [] par;
	delete [] child;
	delete_tree(p);
	delete_tree(c);
	in1.close();
	in2.close();
	out.close();
	
}

