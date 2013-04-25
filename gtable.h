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
    /**
     * @bref  获取第i类数中的第o个数的第k位的rank值
     *
     * @param i
     * @param o
     * @param k
     *
     * @returns   rank[i,o,k]
     */
    int search(int i,int o,int k);
private:
    u64* g;
    int b;
    int size;

    int* cmap;
    //每一个类的数总共占位的累加值
    int* bits_size;
    /**
     * @bref  把g[i]的第l位开始的串设置为v
     *
     * @param i
     * @param l
     * @param v
     */
    void setbits(int i,int l,u64 v);
    /**
     * @bref  init the cmap array
     */
    void makecmap();
};

#endif
