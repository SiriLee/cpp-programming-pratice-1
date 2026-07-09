#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 平衡括号判断
// 关键: 栈(stack), 遇左入右出, 空栈pop时失败
// 参考: core/templates.md 括号匹配

bool check(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '{' || c == '[') {
            st.push(c);
        } else if (c == ')' || c == '}' || c == ']') {
            if (st.empty()) return false;
            char top = st.top();
            if ((c == ')' && top != '(') || (c == '}' && top != '{') || (c == ']' && top != '[')) {
                return false;
            }
            st.pop();
        }
    }
    return st.empty();
}

int main() {
    int n; cin >> n;
    while (n--) {
        string s; cin >> s;
        if (check(s)) {
            cout << "YES" << endl;
        } else {
            cout << "NO" << endl;
        }
    }
    return 0;
}