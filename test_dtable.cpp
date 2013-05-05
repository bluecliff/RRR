#include "dtable.h"
#include <iostream>
#include <string.h>
using namespace std;

int main()
{
    u64 bitvec[10];

    for(int i=0;i<10;i++)
    {
        bitvec[i]=i;
    }
    int n=100;
    int* rank=new int[n];
    memset(rank,0,sizeof(int)*n);

    rank[0]=bitvec[0]&1Ul;
    for(int index=1;index<n;index++)
    {
        int i=index/D;
        int j=index%D;
        if(bitvec[i] & 1UL<<j)
        {
            rank[index]+=rank[index-1];
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
        cout<<(bitvec[i] & (1UL<<j))<<" ";
    }
    cout<<endl;

    for(int index=0;index<n;index++)
    {
        cout<<rank[index]<<" ";
    }
    cout<<endl;
    delete[] rank;
    return 0;
}
