#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 负二进制 (R=-2)
// 关键: floor除法(余数∈[0,1]), n_new = -q (符号翻转)
// 易错: C++ % 结果符号跟随被除数
// 参考: core/base_algo.md §2

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

inline BigInt operator+(const BigInt& a, const BigInt& b) {
    string r;
    int carry = 0, i = a.s.size() - 1, j = b.s.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a.s[i--] - '0';
        if (j >= 0) sum += b.s[j--] - '0';
        r += (sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(r.begin(), r.end());
    return BigInt(r);
}

inline pair<BigInt, int> div_by_int(const BigInt& a, int d) {
    bool neg = a.s[0] == '-';                    // [NEG]
    string num = neg ? a.s.substr(1) : a.s;      // [NEG]
    string q;
    int rem = 0;
    for (char c : num) {
        int cur = rem * 10 + (c - '0');
        int qd = cur / d;
        if (!q.empty() || qd) q += (qd + '0');
        rem = cur % d;
    }
    if (q.empty()) q = "0";
    if (neg && rem > 0) {                        // [NEG]
        q = (BigInt(q) + BigInt("1")).s;          // [NEG]
        rem = d - rem;                            // [NEG]
    }                                             // [NEG]
    if (neg) q = "-" + q;                         // [NEG]
    return {BigInt(q), rem};
}

string dec_to_neg2(BigInt n) {
    if (n.s == "0") return "0";
    string res;
    while (n.s != "0") {
        auto [q, r] = div_by_int(n, 2);       // floor: r ∈ [0,1]
        res += (r + '0');
        string& qs = q.s;                      // n_new = (n-r)/(-2) = -q
        n = BigInt((qs == "0") ? "0" : (qs[0] == '-' ? qs.substr(1) : "-" + qs));
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