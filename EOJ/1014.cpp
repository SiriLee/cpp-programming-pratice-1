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

    BigInt sa(scale(a, flen)), sb(scale(b, flen));
    BigInt res = sa + sb;
    string s = res.s;
    if ((int)s.size() < flen) s.insert(0, flen - s.size(), '0');
    // drop extra fractional digits beyond prec+1 (carries already applied)
    int drop = flen - (prec + 1);
    if (drop > 0) s.erase(s.size() - drop);
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

int main() {
    string A, B; int N;
    cin >> A >> B >> N;
    cout << add_bigfloat(A, B, N) << endl;
    return 0;
}