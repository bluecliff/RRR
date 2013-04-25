/**
 * @file commons.h
 * @bref  一些公共函数声明
 * @author li shuangjiang
 * @version 0.1
 * @date 2013-04-25
 */
#ifndef COMMONS_H_
#define COMMONS_H_


#include "typedef.h"

#ifdef __SSE4_2__
#include <smmintrin.h>
#define POPCOUNT(x) _mm_popcnt_u64(x)
#else
#define POPCOUNT(x) popcount(x)
#endif


u64 popcount(u64 x);

/**
 * @bref  计算组合书C(n,m)
 *
 * @param n
 * @param m
 *
 * @returns
 */
int cal(int n, int m);

int blog(i64 x); //求正整数x的对数

#endif
