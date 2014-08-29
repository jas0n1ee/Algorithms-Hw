#include<iostream>
#include<fstream>
using namespace std;
static int maxnum=0;
void Next(char *p,int *n,int m)
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
int kmp(char *t, char *p,int m,int n,int *r)
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
				i++;
				j++;
				if(j>maxnum) maxnum=j;
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
int main()
{
	char par[]="asdfasdfasdfg";
	char child[]="asdfasdf";
	int *match=new int[strlen(par)];
	int k=kmp(par,child,strlen(par),strlen(child),match);
	cout<<maxnum+(!!k);
}
