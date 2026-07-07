#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

string addBigInt(const string& A, const string& B) {
    vector<int> a(A.rbegin(), A.rend()), b(B.rbegin(), B.rend());
    int n = max(a.size(), b.size());
    a.resize(n, '0');
    b.resize(n, '0');
    vector<int> result(n + 1, 0);
    int carry = 0;
    for (int i = 0; i < n; ++i) {
        int sum = (a[i] - '0') + (b[i] - '0') + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
    result[n] = carry;
    string res;
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        if (res.empty() && *it == 0) continue; // Skip leading zeros
        res.push_back(*it + '0');
    }
    return res;
}

int main() {
    string A, B;
    while (cin >> A >> B) {
        string sum = addBigInt(A, B);
        cout << sum << endl;
    }
    return 0;
}