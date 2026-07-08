#include <iostream>
#include <string>
using namespace std;

// Divide a decimal string by 2, return quotient and set remainder (0 or 1)
string div2(const string& num, int& rem) {
    string res;
    int carry = 0;
    for (char c : num) {
        int cur = carry * 10 + (c - '0');
        res += char(cur / 2 + '0');
        carry = cur % 2;
    }
    rem = carry;
    // Strip leading zeros
    size_t pos = res.find_first_not_of('0');
    return (pos == string::npos) ? "0" : res.substr(pos);
}

// Multiply a decimal string by 2 and add a bit (0 or 1)
string mul2add(const string& num, int bit) {
    string res = num;
    int carry = bit;
    for (int i = res.size() - 1; i >= 0; i--) {
        int cur = (res[i] - '0') * 2 + carry;
        res[i] = char(cur % 10 + '0');
        carry = cur / 10;
    }
    if (carry) res = char(carry + '0') + res;
    return res;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    for (int t = 0; t < T; t++) {
        string N;
        cin >> N;

        // Strip leading zeros from input
        size_t pos = N.find_first_not_of('0');
        if (pos == string::npos) N = "0";
        else if (pos > 0) N = N.substr(pos);

        // Convert to binary; remainders come out LSB-first,
        // which is exactly the reversed binary representation
        string revBin;
        string num = N;
        while (num != "0") {
            int rem;
            num = div2(num, rem);
            revBin += char(rem + '0');
        }

        // Convert reversed binary back to decimal
        string ans = "0";
        for (char bit : revBin) {
            ans = mul2add(ans, bit - '0');
        }

        cout << "case #" << t << ":\n" << ans << "\n";
    }
    return 0;
}
