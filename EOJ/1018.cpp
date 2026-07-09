#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Fraction {
    ll p, q;

    Fraction(ll p = 0, ll q = 1) : p(p), q(q) { normalize(); }
    Fraction(const string& s) {
        size_t pos = s.find('/');
        if (pos == string::npos) {
            p = stoll(s);
            q = 1;
        } else {
            p = stoll(s.substr(0, pos));
            q = stoll(s.substr(pos + 1));
        }
        normalize();
    }

    void operator+=(const Fraction& rhs) {
        p = p * rhs.q + rhs.p * q;
        q *= rhs.q;
        normalize();
    }

    void normalize() {
        if (q < 0) p = -p, q = -q;
        ll g = gcd(abs(p), q);
        p /= g, q /= g;
    }
};

int main() {
    int n; cin >> n;
    Fraction sum;
    while (n--) {
        string s; cin >> s;
        sum += Fraction(s);
    }
    cout << sum.p << '/' << sum.q << '\n';
}