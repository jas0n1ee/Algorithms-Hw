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
	else if(t->lchild!=NULL&&t->rchild!=NULL)
	{
		l[i]=2;
		mark(t->lchild,l);
		mark(t->rchild,l);
	}
	else
	{
		l[i]=1;
		mark(t->lchild,l);
		mark(t->rchild,l);
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
	
	mark(p,par);
	i=-1;
	mark(c,child);
	for(int j=0;j<p->sum;j++) cout<<par[j];
	cout<<endl;
	for(int i=0;i<c->sum;i++) cout<<child[i];

	delete [] par;
	delete [] child;
	delete_tree(p);
	delete_tree(c);
	in1.close();
	in2.close();
	out.close();
	
}

