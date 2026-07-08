#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// 小整数进制转换 (R: 2~36)
ll str_to_ll(const string& s, int R);
string ll_to_str(ll num, int R);
// 小浮点数进制转换
double str_to_double(const string& s, int R);
string double_to_str(double num, int R, int prec = 10);
// 大整数进制转换
string str_to_dec(const string& s, int from);
string dec_to_str(const string& dec, int to);

#endif
