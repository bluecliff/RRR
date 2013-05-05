/**
 * @file dtable.cpp
 * @bref  implementation of class dtable
 * @author li shuangjiang
 * @version 0.1
 * @date 2013-04-25
 */
#include "dtable.h"
#include "compactIntArray.h"
#include "commons.h"

#include <cmath>

void makecmap(int* cmap,u64 total)
{
	int* sum=new int[b+1];
    memset(sum,0,sizeof(int)*(b+1));
    for(u64 i=1;i<total;i++)
    {
        this->cmap[i]=++sum[popcount(i)];
    }
    delete[] sum;
}

dtable::datble()
{
	this->size=0;
    this->b=0;
    this->s=0;

    this->p=NULL;
    this->r=NULL;

    this->l=NULL;
    this->q=NULL;
}

dtable::dtable(u64* bitvec,int* rank,int n)
{
	//直接带入公式的话s不一定是b的整数倍，这样子太恶心了，故做了一些小调整，保证s是b的整数倍
	this->b=(blog(n)+1)/2;
	this->s=2*b*(blog(n)+1);

    //this->s=pow(blog(n),2);
    //this->b=blog(n)/2;

	this->size=n;

	this->r=new compactIntArray(size/s,rank[n-1]);
	//最大数可以是s-b
	this->q=new compactIntArray((size/s+1)*(s/b-1),s);

	for(int i=s;i<n;i+=s)
	{
		r[i/s-1]=rank[i-1];
	}

	int step=0;
	for(int i=b;i<n;i+=b)
	{
		if(i<s)
		{
			q[step++]=rank[i-1];
		}
		else
		{
			q[step++]=rank[i-1]-r[i/s-1];
		}
	}



    u64 total=1UL<<this->b;
    int* cmap=new int[total];
	makecmap(cmap,total);
/*
	//this->p=new compactIntArray(size/s+1,s);
	u32* temp_p=new u32[size/s];
	//u32* temp_l=new u32[(size/s+1)*(s/b-1)];
	u32* temp_l=new u32[size/b-size/s];

	for(int no=0;no<(n/b+1);no++)
	{
		//取出no*b位置开始的b个01序列
		int index=no*b;
		int i=index/D;
		int j=index%D;
		int hole=D-j;
		//向d中写入一个c,o对
		if(hole >= b)
		{
			u64 v = (bitvec[i] >> j)&((1UL-1) >> (D-b));
			if(v==0)
			{
				d->setbits(1,0);
				continue;
			}
			int c = popcount(v);
			int o = cmap[v];
			d->setbits(blog(b)+1,c);
			d->setbits(blog(cal(b,c))+1,o);
		}
		else
		{
			u64 v_low = (bitvec[i] >> j);
			u64 v_high = (bitvec[i+1] & (1UL>>(D-b+hole))) << hole;
			u64 v = v_low+v_high;
			if(v==0)
			{
				d->setbits(1,0);
				continue;
			}
			int c = popcount(v);
			int o = cmap[v];
			d->setbits(blog(b)+1,c);
			d->setbits(blog(cal(b,c))+1,o);
		}
		//写入完成
		if((index+b)%s==0)
		{
			temp_p[(index+b)/s-1]=d.getsize();
		}
		else
		{
			temp_l[(index+b)/b-1-(index+b)/s]=d.getsize();
		}
	}

*/

	u32* temp_p=new u32[n/s+1];
	u32* temp_l=new u32[n/b+1];
	memset(temp_p,0,sizeof(u32)*(n/s+1));
	memset(temp_l,0,sizeof(u32)*(n/b+1));

	for(int no=0;no<(n/b);no++)
	{
		//取出no*b位置开始的b个01序列
		int index=no*b;
		int i=index/D;
		int j=index%D;
		int hole=D-j;
		//向d中写入一个c,o对
		if(hole >= b)
		{
			u64 v = (bitvec[i] >> j)&((1UL-1) >> (D-b));
			if(v==0)
			{
				d->setbits(1,0);
				continue;
			}
			int c = popcount(v);
			int o = cmap[v];
			d->setbits(blog(b)+1,c);
			d->setbits(blog(cal(b,c))+1,o);
		}
		else
		{
			u64 v_low = (bitvec[i] >> j);
			u64 v_high = (bitvec[i+1] & (1UL>>(D-b+hole))) << hole;
			u64 v = v_low+v_high;
			if(v==0)
			{
				d->setbits(1,0);
				continue;
			}
			int c = popcount(v);
			int o = cmap[v];
			d->setbits(blog(b)+1,c);
			d->setbits(blog(cal(b,c))+1,o);
		}
		//写入完成
		if((index+b)%s==0)
		{
			temp_p[(index+b)/s]=d.getsize();
		}
		temp_l[(index+b)/b]=d.getsize()-temp_p[(index+b)/s];
	}

	//处理最后有半个b块的情况
	if(n%b)
	{
		int index=n-n%b;
		int i=index/D;
		int j=index%D;
		int hole=D-j;
		if(hole>=(n%b))
		{
			u64 v = bitvec[i]>>j;
			if (v==0)
			{
				d.setbits(1,0);
			}
			else
			{
				int c=popcount(v);
				int o=cmap[v];
				d.setbits(blog(b)+1,c);
				d.setbits(blog(cal(b,c))+1,o);
			}
		}
		else
		{
			u64 v_low = bitvec[i]>>j;
			u64 v_high = bitvec[i+1]<<hole;
			int c=popcount(v_low+v_high);
			int o=cmap[v_low+v_high];
			d.setbits(blog(b)+1,c);
			d.setbits(blog(cal(b,c))+1,o);
		}
	}

	this->p=new compactIntArray(temp_p+1,size/s,temp_p[size/s]);
	this->l=new compactIntArray(temp_l+1,size/b,temp_l[size/b]);

	delete[] temp_l;
	delete[] temp_p;
	delete[] cmap;
}


dtable::init()
{

}

~dtable::dtable()
{

    this->b=0;
    this->s=0;

    delete this->p;
    delete this->r;
    delete this->l;
    delete this->q;
}

