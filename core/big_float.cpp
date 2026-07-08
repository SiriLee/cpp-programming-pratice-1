#include "big_float.h"
#include "big_int.h"

static string scale(const string& s, int flen) {
    size_t p = s.find('.');
    string i = (p == string::npos) ? s : s.substr(0, p);
    string f = (p == string::npos) ? "" : s.substr(p + 1);
    f.append(flen - f.size(), '0');
    return i + f;
}

static string float_op(const string& a, const string& b, int prec, bool add) {
    int flen = prec + 1;
    BigInt sa(scale(a, flen)), sb(scale(b, flen));
    BigInt res = add ? sa + sb : sa - sb;
    string s = res.s;
    if ((int)s.size() < flen) s.insert(0, flen - s.size(), '0');
    // round half-up
    char last = s.back(); s.pop_back();
    if (last >= '5') s = (BigInt(s) + BigInt("1")).s;
    if ((int)s.size() < prec) s.insert(0, prec - s.size(), '0');
    if (prec > 0) {
        s.insert(s.size() - prec, 1, '.');
        if (s[0] == '.') s.insert(0, "0");
    }
    return s;
}

string add_bigfloat(const string& a, const string& b, int prec) {
    return float_op(a, b, prec, true);
}

string sub_bigfloat(const string& a, const string& b, int prec) {
    return float_op(a, b, prec, false);
}
