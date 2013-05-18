#include "rrr.h"
#include <string.h>

rrr::rrr()
{
	this->bitlength=0;
	this->d=0;
	this->g=0;
}

rrr::rrr(int n,u64* bitvec)
{
	bitlength=n;
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
	d=new dtable(bitvec,rank,n);
	g=new gtable(d->get_b());

	delete[] rank;
}

rrr::~rrr()
{
	this->bitlength=0;
	delete d;
	delete g;
}
int rrr::rank(int index)
{
	int c;
	int o;
	d->searchd(index,&c,&o);
	int ret1=d->searchdir(index);
	int ret2=g->search(c,o,index%(d->get_b()));
	return ret1+ret2;
}
int rrr::getbit(int index)
{
	if(index==0)
		return this->rank(0);
	else
		return this->rank(index)-this->rank(index-1);
}
bool rrr::write(ofstream& fout)
{
	if(fout.is_open())
	{
		fout.write((char*)&bitlength,sizeof(int));
		if(fout.fail() || fout.bad())
			return false;
		if(d->write(fout)) //&& g->write(fout))
			return true;
		else
			return false;
	}
	return false;
}
