#ifndef PARSER_H
#define PARSER_H

#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using namespace boost::multiprecision;
using ll = long long;

// ---- 小整数 (R: 2~36) ----

inline ll str_to_ll(const string& s, int R) {
    return stoll(s, nullptr, R);
}

inline string ll_to_R(ll num, int R) {
    if (num == 0) return "0";
    bool neg = num < 0;                               // [NEG]
    if (neg) num = -num;                              // [NEG]
    string res;
    while (num) {
        int d = num % R;
        res += (d < 10 ? d + '0' : d - 10 + 'A');
        num /= R;
    }
    if (neg) res += '-';                              // [NEG]
    reverse(res.begin(), res.end());
    return res;
}

// ---- 小浮点数 ----
// _frac_xxx = 仅小数部分的核心算法；公开函数 = 切分整数/小数 + 调用核心

inline int _c2d(char c) {
    if (isdigit(c)) return c - '0';
    if (c >= 'A' && c <= 'Z') return c - 'A' + 10;
    return c - 'a' + 10;
}

// 核心：R进制小数部分 → 数值（分子分母算法）
inline double _frac_to_val(const string& frac, int R) {
    ll num = 0, den = 1;
    for (char c : frac) {
        num = num * R + _c2d(c);
        den *= R;
    }
    return (double)num / den;
}

// 切分 + _frac_to_val
inline double str_to_double(const string& s, int R) {
    bool neg = s[0] == '-';                          // [NEG]
    size_t start = neg ? 1 : 0;                       // [NEG]
    size_t dot = s.find('.');
    if (dot != string::npos && dot < start) dot = string::npos;
    string int_part = (dot == string::npos) ? s.substr(start) : s.substr(start, dot - start);
    string frac_part = (dot == string::npos) ? "" : s.substr(dot + 1);

    double val = int_part.empty() ? 0 : str_to_ll(int_part, R);
    if (!frac_part.empty()) val += _frac_to_val(frac_part, R);
    return neg ? -val : val;                         // [NEG]
}

// 核心：小数数值 → R进制串
inline string _val_to_frac(double frac, int R, int prec) {
    string res;
    while (prec--) {
        frac *= R;
        int d = (int)frac;
        res += (d < 10 ? d + '0' : d - 10 + 'A');
        frac -= d;
    }
    return res;
}

// 切分 + _val_to_frac
inline string double_to_R(double val, int R, int prec = 10) {
    bool neg = val < 0;                               // [NEG]
    if (neg) val = -val;                              // [NEG]
    ll int_part = (ll)val;
    string res = ll_to_R(int_part, R);
    if (prec > 0) res += "." + _val_to_frac(val - int_part, R, prec);
    return neg ? "-" + res : res;                     // [NEG]
}

// ---- 大整数 ----

inline string str_to_dec(const string& s, int R) {
    cpp_int res = 0;
    for (char c : s) {
        int d = _c2d(c);
        res = res * R + d;
    }
    return res.str();
}

inline string dec_to_R(const string& dec, int R) {
    cpp_int n(dec);
    if (n == 0) return "0";
    string res;
    while (n != 0) {
        int r = (int)(n % R);
        res += (r < 10 ? r + '0' : r - 10 + 'A');
        n /= R;
    }
    reverse(res.begin(), res.end());
    return res;
}

#endif
