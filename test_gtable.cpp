#include <iostream>
using namespace std;
#include "gtable.h"
#include "commons.h"

int main()
{
    int b=15;
    gtable g(b);

	for(u64 i=1;i<(1<<b);i++)
	{
		//cout<<i<<endl;
		int c = popcount(i);
		int o = g.cmap[i];
		/*for(int k=0;k<b;k++)
		{
			if(i&(1UL<<k))
				cout<<"1\t";
			else
				cout<<"0\t";
		}
		cout<<endl;
		*/
		int rank=0;
		for(int k=0;k<b;k++)
		{
			if(i&(1UL<<k))
				++rank;
				//cout<<++rank<<"\t";
			//else
				//cout<<rank<<"\t";
			if(rank!=g.search(c,o,k))
				cout<<"erro: "<<i<<endl;
		}
		/*
		cout<<endl;
		for(int k=0;k<b;k++)
		{
			cout<<g.search(c,o,k)<<"\t";
		}
		cout<<endl;
		cout<<endl;
		*/
	}

	/*
    for(int i=1;i<=b;i++)
    {
        for(int j=0;j<cal(b,i);j++)
        {
            cout<<i<<" "<<j<<endl;
			cout<<"\t";
			for(int t=0;t<b;t++)
			{

			}
			cout<<"\t";
            for(int t=0;t<b;t++)
                cout<<g.search(i,j,t)<<" ";
			cout<<endl;
        }
		cout<<endl;
    }
	*/
    return 0;
}

