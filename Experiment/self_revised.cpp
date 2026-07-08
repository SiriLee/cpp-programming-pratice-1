#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

string decStrToBinary(const string& num) {
    // Work with individual decimal digits (0-9) in a vector
    vector<int> digits;
    digits.reserve(num.size());
    for (char c : num) {
        digits.push_back(c - '0');
    }

    string bits;
    // At most 334 bits for 10^100, but we stop early when number hits 0
    bits.reserve(340);

    while (true) {
        // Current number's parity → next bit (LSB first)
        bits.push_back(static_cast<char>((digits.back() & 1) + '0'));

        // Divide the whole number by 2 (simulated long division)
        vector<int> quotient;
        quotient.reserve(digits.size());
        int rem = 0;

        for (int d : digits) {
            int cur = rem * 10 + d;
            // Skip leading zeros in quotient (same as hand division:
            // 0123 ÷ 2, we write "61" not "061")
            if (!quotient.empty() || (cur >> 1) != 0) {
                quotient.push_back(cur >> 1);
            }
            rem = cur & 1;
        }

        if (quotient.empty()) break;   // number fully reduced to 0
        digits = move(quotient);
    }

    return bits;
}

string addBigInt(const string& A, const string& B) {
    vector<int> a, b;
    a.reserve(A.size());
    b.reserve(B.size());
    for (int i = static_cast<int>(A.size()) - 1; i >= 0; --i) a.push_back(A[i] - '0');
    for (int i = static_cast<int>(B.size()) - 1; i >= 0; --i) b.push_back(B[i] - '0');

    size_t n = max(a.size(), b.size());
    a.resize(n, 0);
    b.resize(n, 0);

    vector<int> result(n + 1, 0);
    int carry = 0;
    for (size_t i = 0; i < n; ++i) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
    result[n] = carry;

    // Build result string (most significant digit first), skip leading zeros
    string res;
    for (int i = static_cast<int>(result.size()) - 1; i >= 0; --i) {
        if (res.empty() && result[i] == 0) continue;
        res.push_back(static_cast<char>(result[i] + '0'));
    }
    return res.empty() ? "0" : res;
}

string binaryToDecStr(const string& binary) {
    string result = "0";
    for (char c : binary) {
        string doubled = addBigInt(result, result);     // result * 2
        result = addBigInt(doubled, string(1, c));      // + current bit
    }
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        string num;
        cin >> num;

        string revBin = decStrToBinary(num);

        string ans = binaryToDecStr(revBin);

        cout << "case #" << t << ":\n" << ans << "\n";
    }

    return 0;
}
