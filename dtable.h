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

class compactIntArray;

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

    /**
     * @bref  初始化d表及辅助表，由构造函数调用
     *
     * @returns   成功返回true，失败false
     */
    bool init();
    /**
     * @bref   搜索d表，查找到第i个位所对应的(o,c)
     *
     * @param i
     * @param o
     * @param j
     */
    void searchd(int i,int*o,int* c);
    /**
     * @bref  查找第i个位置所在block的基准rank值
     *
     * @param i
     *
     * @returns
     */
    int searchrank(int i);
private:
    /**
     * @bref  d表的基本存储类型，存储由(o,c)对组成的01序列
     */
    u64* d;
    /**
     * @bref  d的字大小
     */
    int size;
    /**
     * @bref    bitvector的分块后的block的位长
     */
    int b;
    /**
     * @bref  bitvector的分块后的super block的位长
     */
    int s;

    /**
     * @bref  存储每一个superblock的(o,c)对在d上的偏移量
     */
    compactIntArray* p;
    /**
     * @bref  存储没一个superblock的基本rank值
     */
    compactIntArray* r;

    /**
     * @bref  存储每一个block的(o,c)对相对于所在superblock的(o,c)对的偏移量
     */
    compactIntArray* l;
    /**
     * @bref  存储每一个block的相对于所在superblock的rank值
     */
    compactIntArray* q;

};

#endif
