#include<iostream>
#include<cstring>
#include<fstream>
using namespace std;
struct data
{
	unsigned int id;
	float math;
	float chinese;
};
int main(int *argc,char *argv[])
{
	fstream in(argv[1],ios::in);
	fstream out_num(argv[2],ios::out);
	fstream out_sco(argv[3],ios::out);
	return 0;

}
