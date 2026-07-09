#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 整数幂 A^B mod C
// 关键: 快速幂模板 qpow
// 参考: core/algo.h

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