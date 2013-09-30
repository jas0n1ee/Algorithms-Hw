#include<stdio.h>
struct CrosLNode
{
	int row,col;
	double val;
	CrosLnode *down, *right;
};
struct CNode
{
	int row,col;
	CNode *next;
	CrosLNode *down, *right;
};


