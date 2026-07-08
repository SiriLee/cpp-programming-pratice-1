#include "big_int.h"

BigInt::BigInt(const string& s) {
    v = s;
    strip0(v);
}

void BigInt::strip0(string& s) {
    size_t p = s.find_first_not_of('0');
    if (p == string::npos) s = "0";
    else if (p > 0) s.erase(0, p);
}

void BigInt::strip_trailing0(string& s) {
    size_t p = s.find_last_not_of('0');
    if (p == string::npos || p == s.size() - 1) return;
    s.erase(p + 1);
}

int cmp(const BigInt& a, const BigInt& b) {
    if (a.v.size() != b.v.size())
        return a.v.size() < b.v.size() ? -1 : 1;
    if (a.v == b.v) return 0;
    return a.v < b.v ? -1 : 1;
}

BigInt operator+(const BigInt& a, const BigInt& b) {
    string r;
    int carry = 0, i = a.v.size() - 1, j = b.v.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a.v[i--] - '0';
        if (j >= 0) sum += b.v[j--] - '0';
        r += (sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(r.begin(), r.end());
    return BigInt(r);
}

BigInt operator-(const BigInt& a, const BigInt& b) {
    string r;
    int borrow = 0, i = a.v.size() - 1, j = b.v.size() - 1;
    while (i >= 0 || j >= 0) {
        int da = (i >= 0) ? a.v[i--] - '0' : 0;
        int db = (j >= 0) ? b.v[j--] - '0' : 0;
        int diff = da - db - borrow;
        if (diff < 0) { diff += 10; borrow = 1; }
        else borrow = 0;
        r += (diff + '0');
    }
    while (r.size() > 1 && r.back() == '0') r.pop_back();
    reverse(r.begin(), r.end());
    return BigInt(r);
}

BigInt operator*(const BigInt& a, const BigInt& b) {
    if (a.v == "0" || b.v == "0") return BigInt("0");
    vector<int> res(a.v.size() + b.v.size(), 0);
    for (int i = a.v.size() - 1; i >= 0; --i)
        for (int j = b.v.size() - 1; j >= 0; --j)
            res[i + j + 1] += (a.v[i] - '0') * (b.v[j] - '0');
    for (int k = res.size() - 1; k > 0; --k) {
        res[k - 1] += res[k] / 10;
        res[k] %= 10;
    }
    string r;
    for (int x : res) if (!r.empty() || x) r += (x + '0');
    return BigInt(r.empty() ? "0" : r);
}

pair<BigInt, int> div_by_int(const BigInt& a, int d) {
    string q;
    int rem = 0;
    for (char c : a.v) {
        int cur = rem * 10 + (c - '0');
        int qd = cur / d;
        if (!q.empty() || qd) q += (qd + '0');
        rem = cur % d;
    }
    if (q.empty()) q = "0";
    return {BigInt(q), rem};
}
