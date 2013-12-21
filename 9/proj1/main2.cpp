#include<iostream>
using namespace std;
static int N;
static int *arr;
static int *L,*M,*pre;
int search(int *a,int num, int k)
{
 	int low=0, high=k-1;
 	while(low<=high)
 	{
		int mid=(low+high)/2;
 		if(num>a[mid])
 		low=mid+1;
 		else
		high=mid-1;
	}
	return low;
} 
int LIS(int *t)
{
	int k=1,j=0;
	L[0]=arr[0];
	M[0]=0;
	pre[0]=-1;
	for(int i=1;i<N;i++)
	{
		j=search(L,arr[i],k);
		L[j]=arr[i];
		M[j]=i;
		if(j>0) pre[i]=M[j-1];
		else pre[i]=-1;
		if(j+1>k) k++;
	}
	cout<<k<<endl;
	j=M[k-1];
	for(int i=k-1;i>=0&&j!=-1;i--)
	{
		t[i]=arr[j];
		j=pre[j];
	}
}
int main()
{
	cin>>N;
	arr=new int[N];
	M=new int[N];
	L=new int[N];
	pre=new int[N];
	int *t=new int [N];
	for(int i=0;i<N;i++) cin>>arr[i];
	LIS(t);
	for(int i=0;i<N;i++) cout<<t[i]<<" ";
	delete []arr;
	delete []M;
}
