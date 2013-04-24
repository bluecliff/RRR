/**
 * @file bitvector.h
 * @bref  为数组的实现
 * @author li shuangjiang
 * @version 0.1
 * @date 2013-04-21
 */
#ifndef BIT_VECTOR_H_
#define BIT_VECTOR_H_

#include <typedef.h>

#include <fstream>
#define D (sizeof(u64)*8)

using namespace std;

/**
 * @bref  位数组
 */
class bitvec_t
{
public:
    bitvec_t();
    /**
     * @bref  创建位数组
     *
     * @param bits 01序列
     * @param n 64位数组的长度
     * @param bits_size 01串的长度
     */
    bitvec_t(u64* bits,i64 n,i64 bits_size);
    ~bitvec_t();
    void init(i64 n);
    i64 setbit(i64 i,int x);
    i64 getbit(i64 i,int x);

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
    /**
     * @bref  存储g表的字符串
     */
    u64* bitvec;
    /**
     * @bref  g表的字长度，每一个字是一个u64
     */
    i64 size;
    //辅助数组，存储每个数在做输分类的第几个数
    int* cmap;
    //每一个类的数总共占位的累加值
    int* bits_size;

    /**
     * @bref  把bitvec[i]的第l位开始的串设置为v
     *
     * @param i
     * @param l
     * @param v
     */
    void setbits(int i,int l,u64 v);
};

#endif
