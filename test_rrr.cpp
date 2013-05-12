#include "rrr.h"
#include <iostream>
#include <string.h>
#include <fstream>
#include <cstdlib>
#include <time.h>

using namespace std;

int main(int argc,char* argv[])
{
	int m=atoi(argv[1]);
	int n= 1<<m;
	//int n=1u<<30;
	u64* bitvec=new u64[n/D+1];
	memset(bitvec,0,sizeof(u64)*(n/D+1));
	for(int i=0;i<n;i++)
	{
		if(i%3)
		{
			bitvec[i/D]|=(1UL<<(i%D));
		}
	}
  	double seconds;



	time_t start=time(NULL);
	rrr r(n,bitvec);
	/*
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
	*/
	time_t end=time(NULL);
	seconds = difftime(end,start);
	
	ofstream fout;
	fout.open("test_rrr.out",ios::binary);
	r.write(fout);
	cout<<n<<"(2^"<<m<<")"<<"\t"<<(end-start)<<"\t"<<fout.tellp()<<endl;	
	fout.close();

	delete[] bitvec;
}
