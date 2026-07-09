#ifndef BIG_FLOAT_H
#define BIG_FLOAT_H
// 备份模块 —— Boost 可用时直接用 cpp_dec_float（见 boost_ref.md）

#include <bits/stdc++.h>
#include "big_int.h"
using namespace std;

static inline string _scale(const string& s, int flen) {
    size_t p = s.find('.');
    string i = (p == string::npos) ? s : s.substr(0, p);
    string f = (p == string::npos) ? "" : s.substr(p + 1);
    if (f.size() < flen) f.append(flen - f.size(), '0');
    return i + f;
}

static inline string _float_op(const string& a, const string& b, int prec, bool add) {
    auto frac_len = [](const string& s) {
        size_t p = s.find('.');
        return (p == string::npos) ? 0 : (int)(s.size() - p - 1);
    };
    int flen = max({frac_len(a), frac_len(b), prec + 1});

    BigInt sa(_scale(a, flen)), sb(_scale(b, flen));
    bool neg = false;                                          // [NEG]
    if (!add && cmp(sa, sb) < 0) { swap(sa, sb); neg = true; } // [NEG]
    BigInt res = add ? sa + sb : sa - sb;
    string s = res.s;
    if ((int)s.size() < flen) s.insert(0, flen - s.size(), '0');
    int drop = flen - (prec + 1);
    if (drop > 0) s.erase(s.size() - drop);
    char last = s.back(); s.pop_back();
    if (last >= '5') s = (BigInt(s) + BigInt("1")).s;
    if ((int)s.size() < prec) s.insert(0, prec - s.size(), '0');
    if (prec > 0) {
        s.insert(s.size() - prec, 1, '.');
        if (s[0] == '.') s.insert(0, "0");
    }
    return neg ? "-" + s : s;                                 // [NEG]
}

inline string add_bigfloat(const string& a, const string& b, int prec) {
    return _float_op(a, b, prec, true);
}

inline string sub_bigfloat(const string& a, const string& b, int prec) {
    return _float_op(a, b, prec, false);
}

#endif
