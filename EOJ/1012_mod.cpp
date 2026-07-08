#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct BigInt {
    string v;
    BigInt(const string& s = "0") {
        v = s;
        strip0(v);
    }
    static void strip0(string& s) {
        size_t p = s.find_first_not_of('0');
        if (p == string::npos) s = "0";
        else if (p > 0) s.erase(0, p);
    }
};

BigInt operator+(const BigInt& a, const BigInt& b) {
    string r;
    int carry = 0, i = a.v.size() - 1, j = b.v.size() - 1;
    while (i >= 0 || j >= 0 || carry) {
        int sum = carry;
        if (i >= 0) sum += a.v[i--] - '0';
        if (j >= 0) sum += b.v[j--] - '0';
        r += (sum % 10 + '0');
        carry = sum / 10;
    }
    reverse(r.begin(), r.end());
    return BigInt(r);
}

int main() {
    string A, B;
    while (cin >> A >> B) {
        string sum = (BigInt(A) + BigInt(B)).v;
        cout << sum << endl;
    }
    return 0;
}