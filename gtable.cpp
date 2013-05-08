/**
 * @file gtable.cpp
 * @bref  实现G表
 * @author li shuangjiang
 * @version 0.1
 * @date 2013-04-21
 */
#include "gtable.h"
#include "commons.h"
#include <cstdlib>
#include <string.h>

gtable::gtable()
{
    this->g=NULL;
    this->b=0;
    this->size=0;
    this->bits_size=NULL;
    this->cmap=NULL;
}

gtable::gtable(int b)
{
    this->b=b;
    //int bits_size=0;
    bits_size=new int[b+1];
    memset(bits_size,0,sizeof(int)*(b+1));
    this->makecmap();
    for(i64 i=1;i<=b;i++)
    {
        bits_size[i]=bits_size[i-1]+(cal(b,i)*(blog(i)+1)*b);
    }
    this->size=bits_size[b]/D+1;
    this->g=new u64[this->size];
	memset(g,0,sizeof(u64)*size);

    for(u64 i=1;i<(1UL<<this->b);++i)
    {
        //i属于第k类的第t个数
        int k=popcount(i);
        int t=this->cmap[i];

        int offset=bits_size[k-1]+t*(blog(k)+1)*b;
        //从offset开始填充01串i的rank值
		u64 rank=0;
        for(int j=1;j<=b;++j)
        {
            //第j-1位的rank值
			if(i & (1UL << (j-1)))
				rank++;
            //rank+=(i & (1UL << (j-1)));
            int m=offset/D;
            int n=offset%D;
            //注意跨字的问题
            if( (D-n) >= (blog(k)+1))
                this->setbits(m,n,rank);
            else
            {
                this->setbits(m,n,rank);
                this->setbits(m+1,0,rank>>(D-n));
            }
            offset+=((blog(k)+1));
        }
    }

}
gtable::~gtable()
{
    delete[] this->g;
    this->b=0;
    this->size=0;
    delete[] this->cmap;
    delete[] this->bits_size;
}

void gtable::makecmap()
{
    u64 total=1UL<<this->b;
    this->cmap=new int[total];
    int* sum=new int[b+1];
    memset(sum,0,sizeof(int)*(b+1));
    for(u64 i=1;i<total;i++)
    {
        this->cmap[i]=sum[popcount(i)]++;
    }
    delete[] sum;
}

void gtable::setbits(int i,int l,u64 v)
{
    this->g[i]=(this->g[i] | (v << l));
}

int gtable::search(int i,int o, int k)
{
    //若是第0类数，明显所有的rank=0;
    if(i==0)
        return 0;
    int offset=this->bits_size[i-1]+o*b*(blog(i)+1)+k*(blog(i)+1);

    //取出offset开始的lg(i)+1位即为所求的值，必须处理跨字的问题
    int m=offset/D;
    int n=offset%D;
    if((D-n)>=(blog(i)+1))
        return (g[m] << (D-n-(blog(i)+1)) >> (D-(blog(i)+1)));
    else
    {
        int low= (g[m] >> n);
        int high= (g[m+1] << (D-((blog(i)+1)-(D-n)))) >> (D-(blog(i)+1));
        return low+high;
    }
}
