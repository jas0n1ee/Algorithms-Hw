#include<iostream>
#include<cmath>
#include<iomanip>
using namespace std;
#define error(x) (abs(x)<0.00001)?1:0
double x1,x2,x3;
double p1,p2,p3,p4;
double a,b,c,d;
double h1,h2,h3;
double A[2][3];
double B[2];
double f1(double x1,double x2)
{
	return -log(1-p1*x1-p2*x2)-log(p3*x1)-log(p4*x2);
}
double f2(double x1,double x2)
{
	return exp(a*x1)-b*log(x1+x2)+c*x1*x1+d*x2*x2;
}
double f3(double x1,double x2,double x3)
{
	return h1*x1*x1+h2*x2*x2+h3*x3*x3;
}
double g2(double x)
{
	return a*a*exp(2*a*x1) - 2*b*d + x1*x1*(4*c*c + 4*d*c) + x1*exp(a*x1)*(4*a*c + 2*a*d);
}
double dg2(double x)
{
	return 2*x1*(4*c*c + 4*d*c) + exp(a*x1)*(4*a*c + 2*a*d) + 2*a*a*a*exp(2*a*x1) + a*x1*exp(a*x1)*(4*a*c + 2*a*d);
}
void solve1()
{
	cin>>x1>>x2;
	cin>>p1>>p2>>p3>>p4;
	cout<<setiosflags(ios_base::fixed)<<setprecision(4);
	cout<<f1(1/(3.0*p1),1/(3.0*p2))<<" "<<1/(3.0*p1)<<" "<<1/(3.0*p2)<<endl;
}
void solve2()
{
	cin>>x1>>x2;
	cin>>a>>b>>c>>d;
	if(x1+x2<=0)
	{
		x1=x2=1;
	}
	double err;
	do
	{
		err=g2(x1)/dg2(x1);
		x1-=g2(x1)/dg2(x1);
	}while(!error(err));
	x2=(2*c*x1+a*exp(a*x1))/(2*d);
	cout<<setiosflags(ios_base::fixed)<<setprecision(4);
	cout<<f2(x1,x2)<<" "<<x1<<" "<<x2<<endl;
}
void solve3()
{
	cin>>x1>>x2>>x3;
	cin>>h1>>h2>>h3;
	for(int i=0;i<2;i++)
		for(int j=0;j<3;j++)
			cin>>A[i][j];
	cin>>B[0]>>B[1];
	x1=(A[0][0]*A[1][1]*A[1][1]*B[0]*h3 + A[0][0]*A[1][2]*A[1][2]*B[0]*h2 + A[0][1]*A[0][1]*A[1][0]*B[1]*h3 + A[0][2]*A[0][2]*A[1][0]*B[1]*h2 - A[0][0]*A[0][1]*A[1][1]*B[1]*h3 - A[0][0]*A[0][2]*A[1][2]*B[1]*h2 - A[0][1]*A[1][0]*A[1][1]*B[0]*h3 - A[0][2]*A[1][0]*A[1][2]*B[0]*h2)/(h3*A[0][0]*A[0][0]*A[1][1]*A[1][1] + h2*A[0][0]*A[0][0]*A[1][2]*A[1][2] - 2*h3*A[0][0]*A[0][1]*A[1][0]*A[1][1] - 2*h2*A[0][0]*A[0][2]*A[1][0]*A[1][2] + h3*A[0][1]*A[0][1]*A[1][0]*A[1][0] + h1*A[0][1]*A[0][1]*A[1][2]*A[1][2] - 2*h1*A[0][1]*A[0][2]*A[1][1]*A[1][2] + h2*A[0][2]*A[0][2]*A[1][0]*A[1][0] + h1*A[0][2]*A[0][2]*A[1][1]*A[1][1]);
	x2=(A[0][1]*A[1][0]*A[1][0]*B[0]*h3 + A[0][1]*A[1][2]*A[1][2]*B[0]*h1 + A[0][0]*A[0][0]*A[1][1]*B[1]*h3 + A[0][2]*A[0][2]*A[1][1]*B[1]*h1 - A[0][0]*A[0][1]*A[1][0]*B[1]*h3 - A[0][1]*A[0][2]*A[1][2]*B[1]*h1 - A[0][0]*A[1][0]*A[1][1]*B[0]*h3 - A[0][2]*A[1][1]*A[1][2]*B[0]*h1)/(h3*A[0][0]*A[0][0]*A[1][1]*A[1][1] + h2*A[0][0]*A[0][0]*A[1][2]*A[1][2] - 2*h3*A[0][0]*A[0][1]*A[1][0]*A[1][1] - 2*h2*A[0][0]*A[0][2]*A[1][0]*A[1][2] + h3*A[0][1]*A[0][1]*A[1][0]*A[1][0] + h1*A[0][1]*A[0][1]*A[1][2]*A[1][2] - 2*h1*A[0][1]*A[0][2]*A[1][1]*A[1][2] + h2*A[0][2]*A[0][2]*A[1][0]*A[1][0] + h1*A[0][2]*A[0][2]*A[1][1]*A[1][1]);
	x3=(A[0][2]*A[1][0]*A[1][0]*B[0]*h2 + A[0][2]*A[1][1]*A[1][1]*B[0]*h1 + A[0][0]*A[0][0]*A[1][2]*B[1]*h2 + A[0][1]*A[0][1]*A[1][2]*B[1]*h1 - A[0][0]*A[0][2]*A[1][0]*B[1]*h2 - A[0][1]*A[0][2]*A[1][1]*B[1]*h1 - A[0][0]*A[1][0]*A[1][2]*B[0]*h2 - A[0][1]*A[1][1]*A[1][2]*B[0]*h1)/(h3*A[0][0]*A[0][0]*A[1][1]*A[1][1] + h2*A[0][0]*A[0][0]*A[1][2]*A[1][2] - 2*h3*A[0][0]*A[0][1]*A[1][0]*A[1][1] - 2*h2*A[0][0]*A[0][2]*A[1][0]*A[1][2] + h3*A[0][1]*A[0][1]*A[1][0]*A[1][0] + h1*A[0][1]*A[0][1]*A[1][2]*A[1][2] - 2*h1*A[0][1]*A[0][2]*A[1][1]*A[1][2] + h2*A[0][2]*A[0][2]*A[1][0]*A[1][0] + h1*A[0][2]*A[0][2]*A[1][1]*A[1][1]);
	cout<<setiosflags(ios_base::fixed)<<setprecision(4);
	cout<<f3(x1,x2,x3)<<" "<<x1<<" "<<x2<<" "<<x3<<endl;
}
int main()
{
	solve1();
	solve2();
	solve3();
}
