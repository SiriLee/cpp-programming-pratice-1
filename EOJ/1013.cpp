#include <bits/stdc++.h>

using namespace std;
using ll = long long;

const int MAXN = 334;

string decStrToBinary(const string& num) {
    string binary;
    vector<int> digits; digits.reserve(num.size());
    for (char c : num) {
        digits.push_back(c - '0');
    }
    for (int i = 0; i < MAXN; ++i) {
        binary.push_back((digits.back() & 1) + '0');
        vector<int> newDigits; int rem = 0;
        newDigits.reserve(digits.size());
        for (int d : digits) {
            int cur = rem * 10 + d;
            if (!newDigits.empty() || (cur >> 1)) {
                newDigits.push_back(cur >> 1);
            }
            rem = cur & 1;
        }
        digits = move(newDigits);
        if (digits.empty()) {
            break;
        }
    }
    reverse(binary.begin(), binary.end());
    while (!binary.empty() && binary.front() == '0') {
        binary.erase(binary.begin());
    }
    if (binary.empty()) binary = "0"; // Handle the case for zero
    return binary;
}

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
    if (res.empty()) res = "0";
    return res;
}

string binaryToDecStr(const string& binary) {
    string result = "0";
    for (char c : binary) {
        result = addBigInt(addBigInt(result, result), string(1, c));
    }
    return result;
}

int main() {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        string num; cin >> num;
        string binary = decStrToBinary(num);
        reverse(binary.begin(), binary.end());
        while (!binary.empty() && binary.front() == '0') {
            binary.erase(binary.begin());
        }
        if (binary.empty()) binary = "0"; // Handle the case for zero
        string decNum = binaryToDecStr(binary);
        cout << "case #" << t << ": \n" << decNum << "\n";
    }
    return 0;
}