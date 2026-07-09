#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 标准进制转换 A→10→B
// 关键: Horner法入(to decimal) + 短除法出(from decimal)
// 参考: core/base_algo.md §1

ll str_to_ll(const string& s, int R);
string ll_to_str(ll num, int R);

ll str_to_ll(const string& s, int R) {
    ll res = 0;
    for (char c : s) {
        int d = isdigit(c) ? c - '0' : c - 'A' + 10;
        res = res * R + d;
    }
    return res;
}

string ll_to_str(ll num, int R) {
    if (num == 0) return "0";
    bool neg = num < 0;
    if (neg) num = -num;
    string res;
    while (num) {
        int d = num % R;
        res += (d < 10 ? d + '0' : d - 10 + 'A');
        num /= R;
    }
    if (neg) res += '-';
    reverse(res.begin(), res.end());
    return res;
}

int main() {
    int A, B; string num;
    cin >> A >> num >> B;
    transform(num.begin(), num.end(), num.begin(), ::toupper);
    ll num_10 = str_to_ll(num, A);
    string result = ll_to_str(num_10, B);
    cout << result << endl;
    return 0;
}