#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 找出最小字符串 (贪心)
// 关键: 遍历选择最小未使用字符

string parse(const string& str) {
    string res;
    char prev = CHAR_MAX;
    int prev_count = 0;
    for (char c : str) {
        if (prev == c) {
            ++prev_count;
        } else if (prev < c) {
            res.append(prev_count, prev);
            prev_count = 1;
        } else {
            prev_count = 1;
        }
        res += c;
        prev = c;
    }
    return res;
}

int main() {
    string str; cin >> str;
    cout << parse(str) << endl;
    return 0;
}