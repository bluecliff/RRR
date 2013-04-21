/**
 * @file gtable.cpp
 * @bref  实现G表
 * @author li shuangjiang
 * @version 0.1
 * @date 2013-04-21
 */
#include "gtable.h"
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

static int blog(i64 x) //求正整数x的对数
{
int l;
  l = 0;
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

gtable::gtable(int i)
{
    this->b=i;

}
~gtable::gtable()
{
    delete[] this->g;
    this->b=0;
    this->size=0;
}
