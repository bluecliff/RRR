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
dtable::datble()
{
    this->size=0;
    this->b=0;
    this->s=0;
    this->d=NULL;

    this->p=NULL;
    this->r=NULL;

    this->l=NULL;
    this->q=NULL;
}

dtable::dtable(u64* bitvec,int* rank,int n)
{
    this->s=pow(blog(n),2);
    this->b=blog(n)/2;

}

~dtable::dtable()
{

    this->size=0;
    this->b=0;
    this->s=0;
    delete[] this->d;

    delete this->p;
    delete this->r;
    delete this->l;
    delete this->q;
}

