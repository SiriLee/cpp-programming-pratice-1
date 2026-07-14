#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct Data
{
    int b; string s;
    ll val;
    Data(int b = 0, const string& s = "") : b(b), s(s) {}
    void getVal() {
        val = stoll(s, nullptr, b);
    }
    bool operator<(const Data& o) const {
        return val < o.val;
    }
};


int main() {
    int n; cin >> n;
    vector<Data> arr;
    for (int i = 0; i < n; ++i) {
        Data d;
        cin >> d.b >> d.s; d.getVal();
        arr.push_back(d);
    }
    stable_sort(arr.begin(), arr.end());
    for (auto& d : arr) {
        cout << d.b << " " << d.s << endl;
    }
    return 0;
}