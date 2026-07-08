#include "big_num.h"

static string strip0(const string& s) {
    size_t p = s.find_first_not_of('0');
    return (p == string::npos) ? "0" : s.substr(p);
}

int cmp_bigint(const string& a, const string& b) {
    string na = strip0(a), nb = strip0(b);
    if (na.size() != nb.size()) return na.size() < nb.size() ? -1 : 1;
    if (na == nb) return 0;
    return na < nb ? -1 : 1;
}

string add_bigint(const string& a, const string& b) {
    string res;
    int carry = 0, i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a[i--] - '0';
        if (j >= 0) sum += b[j--] - '0';
        res += (sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(res.begin(), res.end());
    return res;
}

string sub_bigint(const string& a, const string& b) {
    string res;
    int borrow = 0, i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0) {
        int da = (i >= 0) ? a[i--] - '0' : 0;
        int db = (j >= 0) ? b[j--] - '0' : 0;
        int diff = da - db - borrow;
        if (diff < 0) { diff += 10; borrow = 1; }
        else borrow = 0;
        res += (diff + '0');
    }
    while (res.size() > 1 && res.back() == '0') res.pop_back();
    reverse(res.begin(), res.end());
    return res;
}

string mul_bigint(const string& a, const string& b) {
    if (a == "0" || b == "0") return "0";
    vector<int> res(a.size() + b.size(), 0);
    for (int i = a.size() - 1; i >= 0; --i)
        for (int j = b.size() - 1; j >= 0; --j)
            res[i + j + 1] += (a[i] - '0') * (b[j] - '0');
    for (int k = res.size() - 1; k > 0; --k) {
        res[k - 1] += res[k] / 10;
        res[k] %= 10;
    }
    string r;
    for (int x : res) {
        if (!r.empty() || x) r += (x + '0');
    }
    return r.empty() ? "0" : r;
}

pair<string, int> div_bigint_by_int(const string& num, int d) {
    string q;
    int rem = 0;
    for (char c : num) {
        int cur = rem * 10 + (c - '0');
        int qd = cur / d;
        if (!q.empty() || qd) q += (qd + '0');
        rem = cur % d;
    }
    if (q.empty()) q = "0";
    return {q, rem};
}

// ---- big float helpers ----

static void scale2int(const string& a, const string& b,
                      string& sa, string& sb, size_t& flen) {
    size_t pa = a.find('.'), pb = b.find('.');
    string ai = (pa == string::npos) ? a : a.substr(0, pa);
    string bi = (pb == string::npos) ? b : b.substr(0, pb);
    string af = (pa == string::npos) ? "" : a.substr(pa + 1);
    string bf = (pb == string::npos) ? "" : b.substr(pb + 1);
    flen = max(af.size(), bf.size());
    af.append(flen - af.size(), '0');
    bf.append(flen - bf.size(), '0');
    sa = strip0(ai + af);
    sb = strip0(bi + bf);
}

static string unscale(const string& s, size_t flen) {
    string r = s;
    if (r.size() <= flen) r.insert(0, flen + 1 - r.size(), '0');
    r.insert(r.size() - flen, 1, '.');
    if (r[0] == '.') r.insert(0, "0");
    return r;
}

string add_bigfloat(const string& a, const string& b) {
    string sa, sb;
    size_t flen;
    scale2int(a, b, sa, sb, flen);
    return unscale(add_bigint(sa, sb), flen);
}

string sub_bigfloat(const string& a, const string& b) {
    string sa, sb;
    size_t flen;
    scale2int(a, b, sa, sb, flen);
    return unscale(sub_bigint(sa, sb), flen);
}
