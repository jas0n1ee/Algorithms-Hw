#include<iostream>
#include<stdio.h>
#include<math.h>
#include<cmath>
using namespace std;
#define LarN 100005      //the possible maximum length of input array,please do not alter it
float sorted_float(int N)
{
	float ret=0;
	int b;
	memcpy(&b,&ret,sizeof(int));
	if(N==0)
	{
		ret = 0;
	}
	else 
	{
		if(N>0)
		{
			b|=0x000000;
		}
		else
		{
			b|=0x80000000;
			N=-N;
		}
		unsigned int t1,t2;
		t1=(N-1)%8388607;
		t2=(N-1)/8388607+1;
		if(t2>=255)
		{
			t2=255;
			t1=0;
		}
		b|=t1;
		b|=(t2<<23);
		memcpy(&ret,&b,sizeof(int));
	}
	return ret;
}
void quadratic_solution(double a,double b,double c,double *roots)
{
	double delta,max;
	max=(a>b)?a:b;
	max=(max>c)?max:c;
	a/=max;
	b/=max;
	c/=max;
	delta=b*b-4*a*c;
	if (abs(delta)<sorted_float(1)) roots[0]=roots[1]=-b/(2*a);
	else if(delta<=0) 
	{
		roots[0]=0;
		roots[1]=0;
	}
	else
	{
		if(b>=0)
		{
			roots[0]=((-b-sqrt(delta))/(2*a)>(2*c)/(-b-sqrt(delta)))?(-b-sqrt(delta))/(2*a):(2*c)/(-b-sqrt(delta));
			roots[1]=((-b-sqrt(delta))/(2*a)>(2*c)/(-b-sqrt(delta)))?(2*c)/(-b-sqrt(delta)):(-b-sqrt(delta))/(2*a);
		}
		else
		{
			roots[0]=((-b+sqrt(delta))/(2*a)>(2*c)/(-b+sqrt(delta)))?(-b+sqrt(delta))/(2*a):(2*c)/(-b+sqrt(delta));
			roots[1]=((-b+sqrt(delta))/(2*a)>(2*c)/(-b+sqrt(delta)))?(2*c)/(-b+sqrt(delta)):(-b+sqrt(delta))/(2*a);
		}
	}	
	return;
}

double Kahan_sum(double *x,int N)
{
	double ret,t;
	ret=0;t=0;
	for(int i=0;i<N;i++)
	{
		double a,b;
		a=x[i]-t;
		b=ret+a;
		t=(b-ret)-a;
		ret=b;
	}
	return ret;
}
double ill_conditioned_sum(double *x,int N)
{
	//summation of double array,N is the length of the array
	double ret;
	//your solution goes here
	ret=0;
	return ret;
}
float n_inf=-1.0e100,p_inf=+1.0e100;
int main()
{
	int T_case,N;
	double coefs[3],roots[2],x[LarN];
	float sf;
	//problem 1, sorted float number
	scanf("%d",&T_case);
	while(T_case--){
		scanf("%d",&N);
		sf=sorted_float(N);
		if(sf==p_inf)printf("+1.0e100\n");
		else if(sf==n_inf)printf("-1.0e100\n");
		else printf("%.9e\n",sf);
	}
	//problem 2, solution for quadratic equation
	scanf("%d",&T_case);	
	while(T_case--){
		scanf("%le %le %le",&coefs[0],&coefs[1],&coefs[2]);
		quadratic_solution(coefs[0],coefs[1],coefs[2],roots);
		printf("%.16le %.16le\n",roots[0],roots[1]);
	}
	//problem 3, Kahan summation
	scanf("%d",&T_case);
	while(T_case--){
		scanf("%d",&N);
		for(int i=0;i<N;i++){scanf("%X %X",(int*)(&x[i])+1,(int*)(&x[i]));}
		printf("%.16e\n",Kahan_sum(x,N));
	}

	//problem 4, ill-conditioned summation
	scanf("%d",&T_case);
	while(T_case--){
		scanf("%d",&N);
		for(int i=0;i<N;i++){scanf("%X %X",(int*)(&x[i])+1,(int*)(&x[i]));}
		printf("%.16e\n",ill_conditioned_sum(x,N));
	}
	return 0;
}
