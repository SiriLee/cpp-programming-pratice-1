#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 括号字符串的分数
// 关键: 栈+嵌套深度, 每层贡献由深度决定
// 参考: core/templates.md 括号匹配

const int LEFT = INT_MAX;

int parse(const string& expr) {
    stack<int> st;
    auto add_val = [&](int val) {
        if (st.empty() || st.top() == LEFT) {
            st.push(val);
        } else {
            int prev = st.top();
            st.pop();
            st.push(prev + val);
        }
    };
    for (char c : expr) {
        if (c == '(') {
            st.push(LEFT);
        } else {
            if (st.top() == LEFT) {
                st.pop();
                add_val(1);
            } else {
                int val = st.top();
                st.pop(); st.pop();
                add_val(val * 2);
            }
        }
    }
    return st.top();
}

int main() {
    string expr;
    cin >> expr;
    cout << parse(expr) << endl;
    return 0;
}