/**
 * @file gtable.h
 * @bref  RRR结构中的查询表G
 * @author li shuangjiang
 * @version 0.1
 * @date 2013-04-21
 */
#ifndef GTABLE_H_
#define GTABLE_H_

#include "typedef.h"

/**
 * @bref  计算组合数c(n,m)
 *
 * @param n
 * @param m
 *
 * @returns   组合数值
 */
#define D (sizeof(u64)*8)
int cal(int n, int m);
class gtable
{
public:
    gtable();
    gtable(int b);
    ~gtable();
    int get_rank(int i,int j);
private:
    u64* g;
    int b;
    int size;

    int* cmap;
    void makecmap();
};

#endif
