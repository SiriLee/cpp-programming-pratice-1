#ifndef BIG_FLOAT_H
#define BIG_FLOAT_H

#include <bits/stdc++.h>
using namespace std;

// a + b, 保留 prec 位小数，四舍五入
string add_bigfloat(const string& a, const string& b, int prec);
// a - b (a >= b), 保留 prec 位小数，四舍五入
string sub_bigfloat(const string& a, const string& b, int prec);

#endif
