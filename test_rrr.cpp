#include "rrr.h"
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
	int n=1000;
	u64* bitvec=new u64[n/D+1];
	memset(bitvec,0,sizeof(u64)*(n/D+1));
	for(int i=0;i<n;i++)
	{
		if(i%3)
		{
			bitvec[i/D]|=(1UL<<(i%D));
		}
	}
	rrr r(n,bitvec);
	for(int i=0;i<n;i++)
	{
		cout<<r.getbit(i)<<" ";
	}
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		cout<<r.rank(i)<<" ";
	}
	cout<<endl;


	delete[] bitvec;
}
