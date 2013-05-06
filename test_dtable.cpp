#include "dtable.h"
#include <iostream>
#include <string.h>
#include "commons.h"
using namespace std;

int main()
{
    u64 bitvec[10];

    for(int i=0;i<10;i++)
    {
        bitvec[i]=i+1000;
    }
    int n=200;
    int* rank=new int[n];
    memset(rank,0,sizeof(int)*n);

    rank[0]=bitvec[0]&1Ul;
    for(int index=1;index<n;index++)
    {
        int i=index/D;
        int j=index%D;
        if(bitvec[i] & 1UL<<j)
        {
            rank[index]=1+rank[index-1];
        }
        else
        {
            rank[index]=rank[index-1];
        }
    }
    for(int index=0;index<n;index++)
    {
        int i=index/D;
        int j=index%D;
        if(bitvec[i] & 1UL<<j)
            cout<<"1"<<" ";
        else
            cout<<"0"<<" ";
        // cout<<(bitvec[i] & (1UL<<j))<<" ";
    }
    cout<<endl;

    for(int index=0;index<n;index++)
    {
        cout<<rank[index]<<" ";
    }
    cout<<endl;

    dtable* d=new dtable(bitvec,rank,n);
    for(int i=0;i<n;i++)
    {
        int b=((blog(n)+1)/2);
        int m=i-i%b;
        for(int index=m;index<(m+b) && index<n;index++)
        {
            int i=index/D;
            int j=index%D;
            if(bitvec[i] & 1UL<<j)
                cout<<"1";
            else
                cout<<"0";
        }

        int c,o;
        d->searchd(i,&c,&o);

        cout<<"===="<<i<<":"<<c<<" "<<o<<endl;
    }

    delete d;
    delete[] rank;
    return 0;
}
