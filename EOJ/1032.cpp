#include <bits/stdc++.h>

using namespace std;
using ll = long long;

vector<ll> stepCount(int n) {
    n = max(n, 3);
    vector<ll> steps(n + 1, 0);
    steps[0] = 1;
    steps[1] = 1;
    steps[2] = 2;
    steps[3] = 4;
    for (int i = 4; i <= n; ++i) {
        steps[i] = steps[i - 1] + steps[i - 2] + steps[i - 3] + steps[i - 4];
    }
    return steps;
}

int main() {
    int T; cin >> T;
    vector<int> a(T);
    int max_val = INT_MIN;
    for (int i = 0; i < T; ++i) {
        cin >> a[i];
        max_val = max(max_val, a[i]);
    }
    auto steps = stepCount(max_val);
    for (int i = 0; i < T; ++i) {
        cout << "case #" << i << ":\n";
        cout << steps[a[i]] << endl;
    }
    return 0;
}