#include <bits/stdc++.h>
using namespace std;
using ll = long long;

int n;
long long D;
vector<int> w;

bool check(ll cap) {
    ll days = 0;
    ll cur = 0;
    for (ll x : w) {
        if (x > cap) return false;
        if (cur + x <= cap) {
            cur += x;
        } else {
            ++days;
            cur = x;
        }
        if (days > D) return false;
    }
    if (cur > 0) ++days;
    return days <= D;
}

int main() {
    cin >> n >> D;

    w.resize(n);

    long long sum = 0;
    int min_cap = 0;
    for (int i = 0; i < n; i++) {
        cin >> w[i];
        min_cap = max(min_cap, w[i]);
        sum += w[i];
    }

    long long l = min_cap; 
    long long r = sum;
    long long ans = -1;

    while (l <= r) {
        long long mid = (l + r) / 2;

        if (check(mid)) {
            ans = mid;
            r = mid - 1;
        } else {
            l = mid + 1;
        }
    }

    cout << ans << '\n';

    return 0;
}