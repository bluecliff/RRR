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
#include <fstream>

/**
 * @bref  计算组合数c(n,m)
 *
 * @param n
 * @param m
 *
 * @returns   组合数值
 */
class gtable
{
public:
    gtable();
    gtable(int b);
    ~gtable();
    /**
     * @bref  获取第c类数中的第o个数的第k位的rank值
     *
     * @param c
     * @param o
     * @param k
     *
     * @returns   rank[i,o,k]
     */
    int search(int c,int o,int k);
	bool write(std::ofstream& fout);
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
