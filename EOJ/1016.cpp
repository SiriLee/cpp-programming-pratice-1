#include <bits/stdc++.h>

using namespace std;
using ll = long long;

ll abc(ll A, ll B, int C) {
    ll cur = 1;
    for (ll i = 0; i < B; ++i) {
        cur = (cur * A) % C;
    }
    return cur;
}

int main() {
    ll A, B; int C;
    while (cin >> A >> B >> C) {
        if (A == 0 && B == 0 && C == 0) break;
        cout << abc(A, B, C) << endl;
    }
    return 0;
}