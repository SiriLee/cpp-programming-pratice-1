#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

// ---- 小整数 (R: 2~36) ----
inline ll str_to_ll(const string& s, int R) { return stoll(s, nullptr, R); }
string ll_to_str(ll num, int R);

// ---- 小浮点数 ----
// R进制字符串 → 精确分数 {分子, 分母}（未约分）
pair<ll, ll> str_to_fraction(const string& s, int R);
// R进制字符串 → double（内部用分数计算，避免累积误差）
double str_to_double(const string& s, int R);
// double → R进制字符串
string double_to_str(double num, int R, int prec = 10);

// ---- 大整数 ----
string str_to_dec(const string& s, int from);
string dec_to_str(const string& dec, int to);

#endif
