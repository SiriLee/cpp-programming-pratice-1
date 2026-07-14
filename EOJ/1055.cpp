#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll pow_mod(ll a, ll n, ll mod) {
    ll res = 1;
    while (n) {
        if (n & 1) res = res * a % mod;
        a = a * a % mod;
        n >>= 1;
    }
    return res;
}

int main() {
    int T; cin >> T;
    while (T--) {
        ll A, B; int C;
        cin >> A >> B >> C;
        ll mod = pow(10LL, C);
        ll res = pow_mod(A, B, mod);
        cout << setw(C) << setfill('0') << res << endl;
    }
    return 0;
}