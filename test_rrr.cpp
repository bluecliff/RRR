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
		if(i%10)
		{
			bitvec[i/D]|=(1UL<<(i%D));
		}
	}
  	double seconds;



	rrr r(n,bitvec);

	time_t start=time(NULL);

	for(int i=0;i<n;i++)
	{
		int k=r.getbit(i);
	}
	time_t end=time(NULL);
	double seconds_1=difftime(end,start);
	start=time(NULL);
	for(int i=0;i<n;i++)
	{
		int k=r.rank(i);
	}

	end=time(NULL);
	double seconds_2 = difftime(end,start);

	ofstream fout;
	fout.open("test_rrr.out",ios::binary);
	r.write(fout);
	double ressize=fout.tellp();
	cout<<m<<"\t"<<n<<"\t"<<ressize<<"\t"<<ressize*8.0/n<<"\t"<<seconds_1/n*1000000<<"\t"<<seconds_2/n*1000000<<endl;
	fout.close();

	delete[] bitvec;
}
