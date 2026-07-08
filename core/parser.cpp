#include "parser.h"
#include "big_num.h"

// ---- 小整数 ----

ll str_to_ll(const string& s, int R) {
    ll res = 0;
    for (char c : s) {
        int d = isdigit(c) ? c - '0' : c - 'A' + 10;
        res = res * R + d;
    }
    return res;
}

string ll_to_str(ll num, int R) {
    if (num == 0) return "0";
    bool neg = num < 0;
    if (neg) num = -num;
    string res;
    while (num) {
        int d = num % R;
        res += (d < 10 ? d + '0' : d - 10 + 'A');
        num /= R;
    }
    if (neg) res += '-';
    reverse(res.begin(), res.end());
    return res;
}

// ---- 小浮点数 ----

double str_to_double(const string& s, int R) {
    double res = 0;
    size_t dot = s.find('.');
    size_t int_len = (dot == string::npos) ? s.size() : dot;
    for (size_t i = 0; i < int_len; ++i) {
        int d = isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
        res = res * R + d;
    }
    double frac = 1;
    for (size_t i = dot + 1; i < s.size(); ++i) {
        frac /= R;
        int d = isdigit(s[i]) ? s[i] - '0' : s[i] - 'A' + 10;
        res += d * frac;
    }
    return res;
}

string double_to_str(double num, int R, int prec) {
    bool neg = num < 0;
    if (neg) num = -num;
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
    return neg ? "-" + res : res;
}

// ---- 大整数 ----

string str_to_dec(const string& s, int from) {
    string res = "0";
    for (char c : s) {
        int d = isdigit(c) ? c - '0' : c - 'A' + 10;
        res = mul_bigint(res, to_string(from));
        res = add_bigint(res, to_string(d));
    }
    return res;
}

string dec_to_str(const string& dec, int to) {
    if (dec == "0") return "0";
    string res, num = dec;
    while (num != "0") {
        auto [q, r] = div_bigint_by_int(num, to);
        res += (r < 10 ? r + '0' : r - 10 + 'A');
        num = q;
    }
    reverse(res.begin(), res.end());
    return res;
}
