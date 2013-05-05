/**
 * @file commons.cpp
 * @bref  几个公共函数的实现
 * @author li shuangjiang
 * @version 0.1
 * @date 2013-04-25
 */

#include "commons.h"
u64 popcount(u64 x)
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

int cal(int n, int m)
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

int blog(i64 x) //求整数x的对数
{
    if(x==0)
        return 0;
    int l;
    l = -1;
    while (x>0) {
        x>>=1;
        l++;
    }
    return l;
}
