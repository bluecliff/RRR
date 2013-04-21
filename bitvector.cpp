#include "bitvector.h"

bitvec_t::bitvec_t():bitvec(NULL),size(0),bits_size(0)
{
}
//n为64位整数数组的长度,bits_size为01序列的长度
bitvec_t::bitvec_t(u64* bits, i64 n, i64 bits_size)
{
    this->size=n;
    this->bits_size=bits_size;
    this->bitvec=new u64[size];
    memcpy(bitvec,bits,sizeof(u64)*size);
}

~bitvec_t::bitvec_t()
{
    this->size=0;
    this->bits_size=0;
    delete[] this->bitvec;
}
void bitvec_t init(i64 bits_size)
{
    this->size=bits_size/D+1;
    this->bits_size=bits_size;
    this->bitvec=new u64[this->size];
    memset(this->bitvec,0,sizeof(u64)*this->size);
}
int bitvec_t::setbit(i64 i,int x)
{
    i64 j,l;
    j = i / D;
    l = i % D;
    if (x==0) bitvec[j] &= (~(1L<<l));
    else if (x==1) bitvec[j] |= (1L<<l);
    else {
        printf("error setbit x=%d¥n",x);
        exit(1);
    }
    return x;

}
int bitvec_t::getbit(i64 i, int x)
{
    i64 j,l;

    j = i / D;
    l = i % D;
    return (bitvec[j] >> l) & 1;
}

