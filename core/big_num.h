#ifndef BIG_NUM_H
#define BIG_NUM_H

#include <bits/stdc++.h>
using namespace std;

// 大整数比较：-1 (a<b), 0 (a==b), 1 (a>b)
int cmp_bigint(const string& a, const string& b);
// 大整数 + - *
string add_bigint(const string& a, const string& b);
string sub_bigint(const string& a, const string& b);  // a >= b
string mul_bigint(const string& a, const string& b);
// 大整数除以小整数(2~36)：返回 {商, 余数}
pair<string, int> div_bigint_by_int(const string& num, int d);
// 大浮点数 + -
string add_bigfloat(const string& a, const string& b);
string sub_bigfloat(const string& a, const string& b);  // a >= b
// 去前导零（大整数&大浮点数）
void strip0(string& s);
// 去后导零（大浮点数）
void strip_trailing0(string& s);

#endif
