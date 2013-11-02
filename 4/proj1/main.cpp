#include<iostream>
#include<fstream>
using namespace std;
static int s_max=0,stage=0;
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
	if(t->lchild!=NULL) delete_tree(t->lchild);
	if(t->rchild!=NULL) delete_tree(t->rchild);
	delete t;
}
void outbitree(binode *t,fstream &out)
{
	if(t==NULL) out<<"# ";
	else
	{
		out<<t->data<<" ";
		outbitree(t->lchild,out);
		outbitree(t->rchild,out);
	}
}
void outbitree2(binode *t,fstream &out)
{
	if(t==NULL) out<<"# ";
	else
	{
		out<<t->sum<<" ";
		outbitree2(t->lchild,out);
		outbitree2(t->rchild,out);
	}
}
int main(int argc,char *argv[])
{
	fstream in(argv[1],ios::in);
	fstream out(argv[2],ios::out|ios::trunc);
	binode *root=new binode;
	int temp;
	if(in>>temp) init(temp,root);
	else cerr<<"error";
	while(in>>temp)
	{
		stage=1;
		addchild(root,temp);
		if(stage>s_max) s_max=stage;
	}
	outbitree(root,out);
	out<<"\n\n";
	outbitree2(root,out);
	out<<"\n\n";
	out<<s_max;
	delete_tree(root);
	in.close();
	out.close();
}
