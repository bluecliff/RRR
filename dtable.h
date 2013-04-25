/**
 * @file dtable.h
 * @bref   implementing RRR methord 's D table
 * @author li shuangjiang
 * @version 0.1
 * @date 2013-04-25
 */
#ifndef DTABLE_H_
#define DTABLE_H_
#include "typedef.h"

class dtable
{
public:
    dtable();
    /**
     * @bref
     *
     * @param bitvec bit vector of base 01 sequence
     * @param rank rank values of bit vector
     * @param n lenght of bitvector ,so does rank
     */
    dtable(u64* bitvec,int* rank,int n);
    ~dtable();
private:
    u64* d;
    int size;

};

#endif
