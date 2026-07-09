#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 天平称重 (子集和变种)
// 关键: 每个砝码可选左(+w)/右(-w)/不选, dp第二维偏移sum处理负下标
// 参考: 1031 包含两种实现(二维dp+偏移 / 一维dp子集和)

vector<bool> canWeight(const vector<int>& w, int sum) {
    int n = w.size();
    vector<vector<bool>> dp(n, vector<bool>(2 * sum + 1, false));
    dp[0][sum] = true;
    for (int i = 1; i < n; ++i) {
        for (int j = 0; j <= 2 * sum; ++j) {
            dp[i][j] = dp[i - 1][j] ||
                (j >= w[i] && dp[i - 1][j - w[i]]) ||
                (j + w[i] <= 2 * sum && dp[i - 1][j + w[i]]);
        }
    }
    vector<bool> result(sum + 1, false);
    for (int j = 0; j <= sum; ++j) {
        result[j] = dp[n - 1][j + sum];
    }
    return result;
}

/*
vector<bool> canWeight(vector<int>& w) {
    int sum = accumulate(w.begin(), w.end(), 0);
    vector<bool> dp(sum + 1, false);
    dp[0] = true;
    for (int i = 1; i < w.size(); ++i) {
        for (int j = sum; j >= w[i]; --j) {
            dp[j] = dp[j] || dp[j - w[i]];
        }
    }
    return dp;
}
*/

int main() {
    int n; cin >> n;
    vector<int> w(n + 1);
    for (int i = 1; i <= n; i++) cin >> w[i];
    int sum = accumulate(w.begin(), w.end(), 0);
    auto dp = canWeight(w, sum);
    for (int i = 1; i <= sum; ++i) {
        cout << (dp[i] ? 1 : 0);
    }
    cout << endl;
    return 0;
}