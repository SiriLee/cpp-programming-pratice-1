#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    set<ll> s;
    for (int i = 0; i < n; ++i) {
        int m; cin >> m;
        set<ll> cur;
        for (int j = 0; j < m; ++j) {
            ll a; cin >> a;
            cur.insert(a);
        }
        set<ll> res;
        if (i == 0) res = move(cur);
        else set_intersection(s.begin(), s.end(), cur.begin(), cur.end(), inserter(res, res.begin()));
        s = move(res);
    }
    for (const auto& elem : s) {
        cout << elem << " ";
    }
    return 0;
}