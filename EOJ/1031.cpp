#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using ll = long long;
using namespace boost::multiprecision;

cpp_int max_score(int N, ll T, vector<ll> &time, vector<cpp_int> &score) {
    vector<cpp_int> dp(T + 1, 0);
    for (int i = 0; i < N; ++i) {
        for (ll j = T; j >= time[i]; --j) {
            dp[j] = max(dp[j], dp[j - time[i]] + score[i]);
        }
    }
    return dp[T];
}

int main() {
    int N; ll T;
    cin >> N >> T;
    vector<ll> time(N);
    vector<cpp_int> score(N);
    for (int i = 0; i < N; i++) {
        cin >> time[i] >> score[i];
    }
    cout << max_score(N, T, time, score) << endl;
    return 0;
}