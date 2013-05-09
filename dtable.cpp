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
#include <string.h>

void makecmap(int* cmap,int b,u64 total)
{
	int* sum=new int[b+1];
    memset(sum,0,sizeof(int)*(b+1));
    for(u64 i=1;i<total;i++)
    {
        cmap[i]=sum[popcount(i)]++;
    }
    delete[] sum;
}

dtable::dtable()
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
	this->q=new compactIntArray(size/b,s);

	for(int i=s;i<=n;i+=s)
	{
		r->set(i/s-1,rank[i-1]);
		//r[i/s-1]=rank[i-1];
	}

    for(int i=b;i<=n;i+=b)
    {
        if(i<s)
        {
            q->set(i/b-1,rank[i-1]);
        }
        else
        {
            q->set(i/b-1,rank[i-1]-rank[i-i%s-1]);
        }
    }

    /**********考虑到每个大块的地一个小块的rank都是0,理论上这个rank是没必要存储的，注释中的代码是这种思路的实现
     但实际会造成代码的复杂度的提高和容错性能的下降，所以不再才用这种想法*/
    /*********************************************
	int step=0;
	for(int i=b;i<n;i+=b)
	{
		if(i<s)
		{
			//q[step++]=rank[i-1];
			q->set(step,rank[i-1]);
			step++;
		}
		else
		{
			q->set(step,rank[i-1]-r->get(i/s-1));
			step++;
			//q[step++]=rank[i-1]-r[i/s-1];
		}
	}
    *************************************************************/


    u64 total=1UL<<this->b;
    int* cmap=new int[total];
	makecmap(cmap,b,total);
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
			u64 v = (bitvec[i] >> j)&((0UL-1) >> (D-b));
			if(v==0)
			{
				d.setbits(blog(b)+1,0);

			}
            else
            {
			    int c = popcount(v);
                int o = cmap[v];
                d.setbits(blog(b)+1,c);
                d.setbits(blog(cal(b,c))+1,o);
            }
		}
		else
		{
			u64 v_low = (bitvec[i] >> j);
			u64 v_high = (bitvec[i+1] & ((0-1UL)>>(D-b+hole))) << hole;
			u64 v = v_low+v_high;
			if(v==0)
			{
				d.setbits(blog(b)+1,0);
			}
            else
            {
			    int c = popcount(v);
			    int o = cmap[v];
			    d.setbits(blog(b)+1,c);
			    d.setbits(blog(cal(b,c))+1,o);
            }
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
				d.setbits(blog(b)+1,0);
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
            if(v_high+v_low)
            {
			    int c=popcount(v_low+v_high);
			    int o=cmap[v_low+v_high];
			    d.setbits(blog(b)+1,c);
			    d.setbits(blog(cal(b,c))+1,o);
            }
            else
            {
                d.setbits(blog(b)+1,0);
            }
		}
	}

	this->p=new compactIntArray(temp_p+1,size/s,temp_p[size/s]);
	this->l=new compactIntArray(temp_l+1,size/b,s);

	delete[] temp_l;
	delete[] temp_p;
	delete[] cmap;
}

dtable::~dtable()
{

    this->b=0;
    this->s=0;

    delete this->p;
    delete this->r;
    delete this->l;
    delete this->q;
}

int dtable::get_b()
{
	return this->b;
}

void dtable::searchd(int index,int* c,int* o)
{
	int ip=index/s;
	int il=index/b;
    int p_offset,l_offset;
    if(ip==0)
        p_offset=0;
    else
        p_offset=p->get(ip-1);
    if(il==0)
        l_offset=0;
    else
        l_offset=l->get(il-1);
	*c=d.getbits(p_offset+l_offset,blog(b)+1);
    if((*c)==0)
        (*o)=0;
    else
	    *o=d.getbits(p_offset+l_offset+blog(b)+1,blog(cal(b,*c))+1);
}

int dtable::searchdir(int index)
{
     int si=index/s;
     int bi=index/b;
     if(bi==0)
     {
        return 0;
     }
     if(si==0)
     {
         return q->get(bi-1);
     }
     return r->get(si-1)+q->get(bi-1);
}

bool dtable::write(std::ofstream& fout)
{
	if(fout.is_open())
	{
		fout.write((char*)&size,sizeof(int));
		fout.write((char*)&b,sizeof(int));
		fout.write((char*)&s,sizeof(int));
		if(fout.bad()||fout.fail())
			return false;
		if(!d.write(fout))
			return false;

		if(!p->write(fout))
			return false;
		if(!r->write(fout))
			return false;
		if(!l->write(fout))
			return false;
		if(!q->write(fout))
			return false;
		return true;

	}
	return false;
}
