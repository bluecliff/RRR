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
#include <vector>

using namespace std;

/**
 * @bref  实现一个自增长的位数组，可以向其中写入任意宽度的位串，同时提供根据任意位置，取出任意长的串，
 * 这个任意长不大于64，故取出的数返回一个u64即可
 */
class bitvec_t
{
public:
    bitvec_t();
    /**
     * @bref  插入一个宽为k位的01串v(低k位)到序列的第i个位置
     *
     * @param i
     * @param k
     * @param v
     */
    void setbits(u64 i,int k,int v);
    /**
     * @bref  获取第i位起的长为k的01序列
     *
     * @param i
     * @param k
     *
     * @returns
     */
    int getbits(u64 i, int k);
private:
    /**
     * @bref  基础数组，存储01序列
     */
    vector<u64> bitvec;
    /**
     * @bref  01序列的长度
     */
    u64 bit_size;
};

#endif
