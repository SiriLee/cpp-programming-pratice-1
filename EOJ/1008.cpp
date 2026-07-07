#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

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