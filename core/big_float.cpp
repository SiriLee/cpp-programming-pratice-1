#include "big_float.h"
#include <boost/multiprecision/cpp_int.hpp>
using namespace boost::multiprecision;

static string scale(const string& s, int flen) {
    size_t p = s.find('.');
    string i = (p == string::npos) ? s : s.substr(0, p);
    string f = (p == string::npos) ? "" : s.substr(p + 1);
    if (f.size() < flen) f.append(flen - f.size(), '0');
    return i + f;
}

static string float_op(const string& a, const string& b, int prec, bool add) {
    auto frac_len = [](const string& s) {
        size_t p = s.find('.');
        return (p == string::npos) ? 0 : (int)(s.size() - p - 1);
    };
    int flen = max({frac_len(a), frac_len(b), prec + 1});

    auto no0 = [](const string& x) {
        size_t p = x.find_first_not_of('0');
        return (p == string::npos) ? "0" : x.substr(p);
    };
    cpp_int sa(no0(scale(a, flen))), sb(no0(scale(b, flen)));
    bool neg = false;                                          // [NEG]
    if (!add && sa < sb) { swap(sa, sb); neg = true; }         // [NEG]
    cpp_int res;
    if (add) res = sa + sb; else res = sa - sb;
    string s = res.str();
    if ((int)s.size() < flen) s.insert(0, flen - s.size(), '0');
    // drop extra fractional digits beyond prec+1 (carries already applied)
    int drop = flen - (prec + 1);
    if (drop > 0) s.erase(s.size() - drop);
    // round half-up
    char last = s.back(); s.pop_back();
    if (last >= '5') s = (cpp_int(no0(s)) + 1).str();
    if ((int)s.size() < prec) s.insert(0, prec - s.size(), '0');
    if (prec > 0) {
        s.insert(s.size() - prec, 1, '.');
        if (s[0] == '.') s.insert(0, "0");
    }
    return neg ? "-" + s : s;                                 // [NEG]
}

string add_bigfloat(const string& a, const string& b, int prec) {
    return float_op(a, b, prec, true);
}

string sub_bigfloat(const string& a, const string& b, int prec) {
    return float_op(a, b, prec, false);
}
