#include "parser.h"
#include "big_int.h"

// ---- 小整数 ----

string ll_to_str(ll num, int R) {
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

pair<ll, ll> str_to_fraction(const string& s, int R) {
    if (s.empty()) return {0, 1};
    bool neg = s[0] == '-';                          // [NEG]
    size_t start = neg ? 1 : 0;                       // [NEG]
    size_t dot = s.find('.');
    if (dot != string::npos && dot < start) dot = string::npos;
    string int_part = (dot == string::npos) ? s.substr(start) : s.substr(start, dot - start);
    string frac_part = (dot == string::npos) ? "" : s.substr(dot + 1);

    ll num = 0, den = 1;
    for (char c : int_part) {
        int d = isdigit(c) ? c - '0' : (c >= 'A' ? c - 'A' + 10 : c - 'a' + 10);
        num = num * R + d;
    }
    for (char c : frac_part) {
        int d = isdigit(c) ? c - '0' : (c >= 'A' ? c - 'A' + 10 : c - 'a' + 10);
        num = num * R + d;
        den *= R;
    }
    if (neg) num = -num;                             // [NEG]
    return {num, den};
}

double str_to_double(const string& s, int R) {
    auto [num, den] = str_to_fraction(s, R);
    return (double)num / den;
}

string double_to_str(double num, int R, int prec) {
    bool neg = num < 0;                               // [NEG]
    if (neg) num = -num;                              // [NEG]
    ll int_part = (ll)num;
    double frac_part = num - int_part;
    string res = ll_to_str(int_part, R);
    if (prec > 0) {
        res += '.';
        while (prec--) {
            frac_part *= R;
            int d = (int)frac_part;
            res += (d < 10 ? d + '0' : d - 10 + 'A');
            frac_part -= d;
        }
    }
    return neg ? "-" + res : res;                     // [NEG]
}

// ---- 大整数 ----

string str_to_dec(const string& s, int from) {
    BigInt res("0");
    for (char c : s) {
        int d = isdigit(c) ? c - '0' : c - 'A' + 10;
        res = res * BigInt(to_string(from)) + BigInt(to_string(d));
    }
    return res.s;
}

string dec_to_str(const string& dec, int to) {
    if (dec == "0") return "0";
    string res;
    BigInt num(dec);
    while (num.s != "0") {
        auto [q, r] = div_by_int(num, to);
        res += (r < 10 ? r + '0' : r - 10 + 'A');
        num = q;
    }
    reverse(res.begin(), res.end());
    return res;
}
