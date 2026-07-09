#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 0-1背包 (恰好容量M)
// 关键: dp一维优化, 内层j必须倒序(j=M; j>=w[i]; --j)
// 参考: core/templates.md 01背包

ll package01(ll m, const vector<ll>& w, const vector<ll>& v) {
    vector<ll> dp(m + 1);
    for (size_t i = 0; i < w.size(); ++i) {
        for (ll j = m; j >= w[i]; --j) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[m];
}

/*
int packageComplete(int m, const vector<int>& w, const vector<int>& v) {
    vector<int> dp(m + 1);
    for (size_t i = 0; i < w.size(); ++i) {
        for (int j = w[i]; j <= m; ++j) {
            dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
        }
    }
    return dp[m];
}
*/

int main() {
    int T; cin >> T;
    while (T--) {
        int n, M; cin >> n >> M;
        vector<ll> w(n), v(n);
        for (int i = 0; i < n; ++i) cin >> w[i] >> v[i];
        cout << package01(M, w, v) << endl;
    }
    return 0;
}