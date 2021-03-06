//This program has been test under vs2012&MinGW
#include<iostream>
#include<cstring>
#include<fstream>
#include<iomanip>
using namespace std;
struct data
{
	char id[6];
	float math;
	float chinese;
	float sum;
};
struct binode
{
	data stu;
	binode *lchild,*rchild;
};
void init(data stu,binode *t)
{
	t->stu=stu;
	t->lchild=NULL;
	t->rchild=NULL;
}
void addchild_id(binode *t,data stu)
{
	if(strcmp(stu.id,t->stu.id)<0)
	{
		if(t->lchild==NULL)
		{
			t->lchild=new binode;
			t->lchild->stu=stu;
			t->lchild->lchild=NULL;
			t->lchild->rchild=NULL;
		}
		else addchild_id(t->lchild,stu);
	}
	else
	{
		if(t->rchild==NULL)
		{
			t->rchild=new binode;
			t->rchild->stu=stu;
			t->rchild->lchild=NULL;
			t->rchild->rchild=NULL;
		}
		else addchild_id(t->rchild,stu);
	}
}
void addchild_sum(binode *t,data stu)
{
	if(stu.sum > t->stu.sum)
	{
		if(t->lchild==NULL)
		{
			t->lchild=new binode;
			t->lchild->stu=stu;
			t->lchild->lchild=NULL;
			t->lchild->rchild=NULL;
		}
		else addchild_sum(t->lchild,stu);
	}
	else if(stu.sum==t->stu.sum)
	{
		if(strcmp(stu.id,t->stu.id)<0)
		{
			if(t->lchild==NULL)
			{
				t->lchild=new binode;
				t->lchild->stu=stu;
				t->lchild->lchild=NULL;
				t->lchild->rchild=NULL;
			}
			else addchild_sum(t->lchild,stu);
		}
		else
		{
			if(t->rchild==NULL)
			{
				t->rchild=new binode;
				t->rchild->stu=stu;
				t->rchild->lchild=NULL;
				t->rchild->rchild=NULL;
			}
			else addchild_sum(t->rchild,stu);
		}
	}
	else
	{
		if(t->rchild==NULL)
		{
			t->rchild=new binode;
			t->rchild->stu=stu;
			t->rchild->lchild=NULL;
			t->rchild->rchild=NULL;
		}
		else addchild_sum(t->rchild,stu);
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
	if(t==NULL) return; 
	else
	{
		outbitree(t->lchild,out);
		out<<t->stu.id<<" "<<fixed<<setprecision(2)<<t->stu.math<<" "<<t->stu.chinese<<endl;
		outbitree(t->rchild,out);
	}
}
void outbitree2(binode *t,fstream &out)
{
	if(t==NULL) return; 
	else
	{
		outbitree2(t->lchild,out);
		if((strcmp(t->stu.id,"S3000")<=0)&&t->stu.sum>=170) out<<t->stu.id<<" "<<fixed<<setprecision(2)<<t->stu.math<<" "<<t->stu.chinese<<endl;
		outbitree2(t->rchild,out);
	}
}
void del(binode *t,data stu)
{
	binode *child;
	binode *temp;
	if(t==NULL) return;
	if(t->lchild==NULL&&t->rchild==NULL) return;
	if(t->lchild!=NULL&&strcmp(t->lchild->stu.id,stu.id)==0&&t->lchild->stu.math==stu.math&&t->lchild->stu.chinese==stu.chinese)
	{
		child=t->lchild;
		t->lchild=child->lchild;
		child->lchild=NULL;
		if(t->lchild!=NULL)
		{
			temp=t->lchild->rchild;
			if(temp==NULL)
			{
				t->lchild->rchild=child->rchild;
			}
			else
			{
				while(temp->rchild!=NULL){temp=temp->rchild;}
				temp->rchild=child->rchild;
			}
			child->rchild=NULL;
			delete child;
		}
		else
		{
			t->lchild=child->rchild;
			child->rchild=NULL;
			delete child;
		}
	}
	else if(t->rchild!=NULL&&strcmp(t->rchild->stu.id,stu.id)==0&&t->rchild->stu.math==stu.math&&t->rchild->stu.chinese==stu.chinese)
	{
		child=t->rchild;
		t->rchild=child->rchild;
		child->rchild=NULL;
		if(t->rchild!=NULL)
		{
			temp=t->rchild->lchild;
			if(temp==NULL) t->rchild->lchild=child->lchild;
			else
			{
				while(temp->lchild!=NULL){temp=temp->lchild;}
				temp->lchild=child->lchild;
			}
			child->lchild=NULL;
			delete child;
			return;
		}
		else
		{
			t->rchild=child->lchild;
			child->lchild=NULL;
			delete child;
			return;
		}
	}
	else
	{
		del(t->lchild,stu);
		del(t->rchild,stu);
	}
}
int main(int argc,char *argv[])
{
	fstream in(argv[1],ios::in);
	fstream out_num(argv[2],ios::out|ios::trunc);
	fstream out_sco(argv[3],ios::out|ios::trunc);
	fstream out_ser(argv[4],ios::out|ios::trunc);
	fstream in2(argv[5],ios::in);
	fstream out_upd(argv[6],ios::out|ios::trunc);
	fstream in3(argv[7],ios::in);
	fstream out_del(argv[8],ios::out|ios::trunc);
	data temp;
	binode *num=new binode,*sco=new binode;
	in>>temp.id>>temp.math>>temp.chinese;
	temp.sum=temp.math+temp.chinese;
	init(temp,num);
	init(temp,sco);
	while(in>>temp.id)
	{
		in>>temp.math>>temp.chinese;
		temp.sum=temp.math+temp.chinese;
		addchild_id(num,temp);
		addchild_sum(sco,temp);
	}
	outbitree(num,out_num);
	outbitree(sco,out_sco);
	outbitree2(sco,out_ser);
	while(in2>>temp.id)
	{
		in2>>temp.math>>temp.chinese;
		temp.sum=temp.math+temp.chinese;
		addchild_id(num,temp);
	}
	outbitree(num,out_upd);
	while(in3>>temp.id)
	{
		in3>>temp.math>>temp.chinese;
		if(strcmp(sco->stu.id,temp.id)==0&&sco->stu.math==temp.math&&sco->stu.chinese==temp.chinese)
		{
			if(sco->lchild==NULL)
			{
				binode *temp=sco;
				sco=sco->rchild;
				delete temp;
			}
			else
			{
				binode *temp=sco;
				sco=sco->lchild;
				binode *child=sco;
				while(child->rchild!=NULL) child=child->rchild;
				child->rchild=temp->rchild;
				delete temp;
			}
		}
		else del(sco,temp);
	}
	outbitree(sco,out_del);
	delete_tree(num);
	delete_tree(sco);
	in.close();
	out_num.close();
	out_sco.close();
	out_ser.close();
	in2.close();
	out_upd.close();
	return 0;

}
