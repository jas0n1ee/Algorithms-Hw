#include <iostream>
#include <ctime>
#include <cstdlib>
#include <windows.h>
using namespace std;

int ArgvToInt(char* argv)
{
	int int_to_return=0;
	while(*argv!='\0')
	{
		if(*argv>'9'||*argv<'0')
		{
			return -1;
		}
		else
		{
			int_to_return*=10;
			int_to_return+=*argv-'0';
		}
		argv++;
	}
	return int_to_return;
}

int random(double start, double end)
{
    return int(start+(end-start)*rand()/(RAND_MAX + 1.0));
}


int main(int argc,char *argv[])
{
    int random(double, double);
	Sleep(100);
	srand( unsigned ( time (0) ) );
	int V = ArgvToInt(argv[1]);
	int E = random(0, V*(V-1)/2);
	
	int **flagM = new int* [V];
	for (int i=0; i<V; i++)
		flagM[i] = new int [V];
	for (int i = 0; i<V; i++)
		for (int j = 0; j<V; j++)
			if (i==j)
				flagM[i][j] = 1;
			else 
				flagM[i][j] = 0;

	cout<<V<<" "<<E<<endl;
	for(int edgeNumber = 0; edgeNumber < E;)
	{
		int start = random(0, V);
		int end = random(0, V);
		if (flagM[start][end]==0)
		{
			edgeNumber++;
			flagM[start][end] = 1;
			cout<<start<<" "<<end<<" "<<random(1, 1000)<<endl;
		}
	}
	int start = random(0, V);
	int end = random(0, V);
	while (start==end)
	{
		end = random(0, V);
	}
	cout<<start<<" "<<end<<endl;
    return 0;
}
