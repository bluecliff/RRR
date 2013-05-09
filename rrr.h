/**
 * @file rrr.h
 * @bref  实现rank操作的RRR方法
 * @author li shuangjiang
 * @version 0.0.1
 * @date 2013-05-09
 */
#ifndef RRR_H_
#define RRR_H_

#include "dtable.h"
#include "gtable.h"
#include "typedef.h"
#include <fstream>

/**
 * @bref  实现RRR方法的rank操作
 */
class rrr
{
	public:
		rrr();
		/**
		 * @bref  根据给定的位数组初始化RRR结构,初始化后RRR的结构不能再变化
		 *
		 * @param n	位数组的长度
		 * @param bitArray	位数组
		 */
		rrr(int n,u64* bitArray);
		~rrr();
		/**
		 * @bref  获取第i位的rank值
		 *
		 * @param i
		 *
		 * @returns
		 */
		int rank(int i);
		/**
		 * @bref  获取第i位的bit值，0或者1
		 *
		 * @param i
		 *
		 * @returns
		 */
		int getbit(int i);
		bool write(ofstream& fout);
	private:
		int bitlength;
		dtable* d;
		gtable* g;
};



#endif
