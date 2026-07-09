#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

// 考点: 最近点对(一维)
// 关键: 排序后相邻比较, double 用 abs(a-b)<1e-9 判等

int main() {
    int n; cin >> n;
    vector<ll> a(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    sort(a.begin(), a.end());
    ll result = 0;
    for (int i = 0; i < n; i++) {
        if (i % 2) result += a[i];
        else result -= a[i];
    }
    cout << result << endl;
    return 0;
}