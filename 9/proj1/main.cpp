#include<iostream>
using namespace std;
static int N;
static int *arr;
static int *b;
static int *c;
int search(int num, int k)
{
 	int low=0, high=k;
 	while(low<=high)
 	{
		int mid=(low+high)/2;
 		if(num>b[mid])
 		low=mid+1;
 		else
		high=mid-1;
	}
	return low;
} 
int LIS()
{
	int k=0;
	b[0]=arr[0];
	c[0]=arr[0];
	for(int i=1;i<=N;i++)
	{
		if(arr[i]>b[k]) 
		{
			b[++k]=arr[i];
			c[k]=arr[i];
		}
		else
		{
			b[search(arr[i],k)+1]=arr[i];
		}
	}
	return k;
}
int main()
{
	cin>>N;
	arr=new int[N];
	b=new int[N];
	c=new int[N];
	for(int i=0;i<N;i++) cin>>arr[i];
	int a=LIS();
	cout<<a<<endl;
	for(int i=0;i<a;i++) cout<<c[i]<<" ";
	cout<<endl;
	delete []arr;
	delete []b;
	delete []c;
}
