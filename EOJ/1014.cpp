#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
using ll = long long;

string getSum(const string& A, const string& B, int N) {
    int eA = 0, eB = 0;
    list<int> a, b;
    for (auto it = A.rbegin(); it != A.rend(); ++it) {
        if (*it == '.') {
            eA = a.size();
        } else {
            a.push_back(*it - '0');
        }
    }
    for (auto it = B.rbegin(); it != B.rend(); ++it) {
        if (*it == '.') {
            eB = b.size();
        } else {
            b.push_back(*it - '0');
        }
    }
    int e = max(eA, eB);
    // Pad with zeros to make the decimal parts equal
    for (int i = eA; i < e; ++i) a.push_front(0);
    for (int i = eB; i < e; ++i) b.push_front(0);
    int carry = 0;
    int n = max(a.size(), b.size());
    vector<int> sum;
    for (auto itA = a.begin(), itB = b.begin(); itA != a.end() || itB != b.end(); ++itA, ++itB) {
        int digitA = (itA != a.end()) ? *itA : 0;
        int digitB = (itB != b.end()) ? *itB : 0;
        int total = digitA + digitB + carry;
        sum.push_back(total % 10);
        carry = total / 10;
    }
    if (carry > 0) {
        sum.push_back(carry);
    }
    // Convert the result back to a string
    string result;
    int end = e - N > 0 ? (e - N) : 0;
    for (int i = sum.size() - 1; i >= end; --i) {
        result += to_string(sum[i]);
        if (i == e) result += '.';
    }

    return result;
}

int main() {
    string A, B; int N;
    cin >> A >> B >> N;
    cout << getSum(A, B, N) << endl;
    return 0;
}