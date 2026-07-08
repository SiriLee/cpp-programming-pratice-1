#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct BigInt {
    string s;

    BigInt(const string& v = "0") { s = v; strip0(s); }
    BigInt(ll n) : BigInt(to_string(n)) {}

    static void strip0(string& x) {
        size_t p = x.find_first_not_of('0');
        if (p == string::npos) x = "0";
        else if (p > 0) x.erase(0, p);
    }
};

inline int cmp(const BigInt& a, const BigInt& b) {
    if (a.s.size() != b.s.size())
        return a.s.size() < b.s.size() ? -1 : 1;
    if (a.s == b.s) return 0;
    return a.s < b.s ? -1 : 1;
}

inline pair<BigInt, int> div_by_int(const BigInt& a, int d) {
    string q;
    int rem = 0;
    for (char c : a.s) {
        int cur = rem * 10 + (c - '0');
        int qd = cur / d;
        if (!q.empty() || qd) q += (qd + '0');
        rem = cur % d;
    }
    if (q.empty()) q = "0";
    return {BigInt(q), rem};
}

/*
string dec_to_negR(ll n, int R) {
    if (n == 0) return "0";
    string res;
    while (n) {
        int r = n % -R;
        if (r < 0) r += -R;
        n = (n - r) / R;
        res += (r + '0');
    }
    reverse(res.begin(), res.end());
    return res;
}
    */

string dec_to_neg2(BigInt& n) {
    if (n.s == "0") return "0";
    string res;
    while (n.s != "0") {
        bool positive = cmp(n, BigInt("0")) > 0;
        auto [q, r] = div_by_int(n, 2);
        n = q;
    }
    reverse(res.begin(), res.end());
    return res;
}


int main() {
    string dec; cin >> dec;
    BigInt n(dec);
    cout << dec_to_neg2(n) << endl;
    return 0;
}