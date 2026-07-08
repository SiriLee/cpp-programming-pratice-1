#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 334;

struct BigInt {
    string v;
    BigInt(const string& s = "0") {
        v = s;
        strip0(v);
    }
    static void strip0(string& s) {
        size_t p = s.find_first_not_of('0');
        if (p == string::npos) s = "0";
        else if (p > 0) s.erase(0, p);
    }
};

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

string dec_to_str(const string& dec, int to) {
    if (dec == "0") return "0";
    string res; int count = 0;
    BigInt num(dec);
    while (num.v != "0" && count < MAXN) {
        auto [q, r] = div_by_int(num, to);
        res += (r < 10 ? r + '0' : r - 10 + 'A');
        num = q; ++count;
    }
    // reverse(res.begin(), res.end());
    return res;
}

string str_to_dec(const string& s, int from) {
    BigInt res("0");
    for (char c : s) {
        int d = isdigit(c) ? c - '0' : c - 'A' + 10;
        res = (res + res) + BigInt(to_string(d));
    }
    return res.v;
}


int main() {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        string num; cin >> num;
        string rec_res = dec_to_str(num, 2);
        string dec = str_to_dec(rec_res, 2);
        cout << "case #" << t << ": \n" << dec << "\n";
    }
    return 0;
}