#include<iostream>
#include<stdio.h>
using namespace std;
static int N;
static int *arr;
static int *M;
static int *P;
int find_pos(int *B, int len, int value)  
{  
    int left = 0, right = len - 1, middle = 0;  
  
    while (left <= right) {  
        middle = (left + right)>>1;  
        if (B[middle] < value)  
            left = middle + 1;    
        else if (B[middle] == value)  
            left = middle + 1;   
        else  
            right = middle - 1;  
    }  
      
    return left;  
}  
int lis_nlogn(int *p, int len, int *inc_seq)  
{  
    int i = 0, pos = 0, curr_len = 0;  
    int *L = NULL, *prev = NULL, *M = NULL;  
  
    L = new int[len]  ;
    M = new int[len]  ;      
    prev = new int[len]  ; 
  
    L[0] = p[0];  
    M[0] = 0;  
    prev[0] = -1;               /* the prev of the p[0] is NULL */   
    curr_len = 1;  
  
    /* Caculate prev and M */  
    for (i = 1;i < len;i++) {  
        pos = find_pos(L, curr_len, p[i]);  
        L[pos] = p[i];  
        M[pos] = i;  
        if (pos > 0)  
            prev[i] = M[pos - 1];  
        else  
            prev[i] = -1;  
        if (pos + 1 > curr_len)  
            curr_len++;  
    }  
  
    /* Output increasing sequence */  
    cout<<curr_len<<endl;
    pos = M[curr_len - 1];  
    for (i = curr_len - 1;i >= 0 && pos != -1;i--) {  
        cout<<p[pos]<<" ";  
        pos = prev[pos];  
    }  
  	delete []L;
  	delete []M;
  	delete []prev;
    return curr_len;  
}  
int main()
{
	cin>>N;
	arr=new int[N];
	M=new int[N];
	P=new int[N];
	for(int i=0;i<N;i++) cin>>arr[i];
	lis_nlogn(arr,N,M);
}
