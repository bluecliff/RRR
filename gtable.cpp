/**
 * @file gtable.cpp
 * @bref  实现G表
 * @author li shuangjiang
 * @version 0.1
 * @date 2013-04-21
 */
#include "gtable.h"

#ifdef __SSE4_2__
#include <smmintrin.h>
#define POPCOUNT(x) _mm_popcnt_u64(x)
#else
#define POPCOUNT(x) popcount(x)
#endif

static u64 popcount(u64 x)
{
  u64 r;

  r = x;
  r = ((r & 0xaaaaaaaaaaaaaaaa)>>1) + (r & 0x5555555555555555);
  r = ((r & 0xcccccccccccccccc)>>2) + (r & 0x3333333333333333);
  r = ((r>>4) + r) & 0x0f0f0f0f0f0f0f0f;

  r *= 0x0101010101010101;
  r >>= 64-8;

  return r;
}



static int cal(int n, int m)
{
 int i, a, b, p;
 if(n<m){i=m;m=n;n=i;}
 p=1;
 a=n-m<m?n-m:m;
 b=n-m>m?n-m:m;
 for(i=1; i<=a; i++)
     p+=p*b/i;
 return p;
}

static int blog(i64 x) //求正整数x的对数
{
int l;
  l = -1;
  while (x>0) {
    x>>=1;
    l++;
  }
  return l;
}

gtable::gtable()
{
    this->g=NULL;
    this->b=0;
    this->size=0;
}

gtable::gtable(int b)
{
    this->b=b;
    //int bits_size=0;
    int* bits_size=new int[b+1];
    memset(bits_size,0,sizeof(int)*(b+1));
    this->makecmap();
    for(i64 i=1;i<=b;i++)
    {
        bits_size[i]=bits_size[i-1]+(cal(b,i)*(blog(i)+1)*b);
    }
    this->size=bits_size[b]/D+1;
    this->g=new u64[this->size];
    for(u64 i=1;i<(1UL<<this->b);++i)
    {
       int k=popcount(i);
       int t=this->cmap[i]-1;
       int offset=bits_size[k-1]+t*(blog(k)+1)*b;
       this->setbits(this->g,offset,rank());
    }
    //应该按类填充，没一个类中有c(b,i)个块儿需要填充，没一块儿是一个长为b个01的串的rank数组
    for(int i=1;i<b;i++)
    {

    }
}
~gtable::gtable()
{
    delete[] this->g;
    this->b=0;
    this->size=0;
    delete[] this->cmap;
}

void gtable::makecmap()
{
    u64 total=1UL<<this->b;
    this->cmap=new int[total];
    int* sum=new int[b+1];
    memset(sum,0,sizeof(int)*(b+1));
    for(u64 i=1;i<total;i++)
    {
        this->cmap[i]=++sum[popcount(i)];
    }
    delete[] sum;
}
