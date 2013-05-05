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
     * @bref   搜索d表，查找到第i个位所在的(c,o)
     *
     * @param i
     * @param c
     * @param o
     */
    void searchd(int i,int* c,int* o);
private:
	/**
	 * @bref  由c,o对连接起来的01串
	 */
	bitvec_t d;
	/**
	 * @bref  rank表的长度n，对应为原始01序列的长度
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
