#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 最小01串权值
// 关键: 遍历替换?为0/1, 计算相邻不同字符数×权重

void parse(string& str) {
    size_t n = str.size();
    // n >= 2
    for (size_t i = 0; i < n; ++i) {
        char c = str[i];
        if (c != '?') continue;
        if (i == 0) {
            size_t next_i = 0;
            while (next_i != n && str[next_i] == '?') ++next_i;
            char next_c = next_i == n ? '0' : str[next_i];
            for (; i < next_i; ++i) {
                str[i] = next_c;
            }
        } else {
            str[i] = str[i - 1];
        }
    }
}

ll getWeight(int w1, int w2, string& str) {
    ll weight = 0;
    size_t n = str.size();
    if (n <= 1) return 0;  
    parse(str);
    char prev = str[0];
    for (size_t i = 1; i < n; ++i) {
        char cur = str[i];
        if (cur == prev) continue;
        if (prev < cur) weight += w1;
        else weight += w2;
        prev = cur;
    }
    return weight;
}

int main() {
    for (int i = 0; i < 4; ++i) {
        int w1, w2; string str;
        cin >> w1 >> w2 >> str;
        cout << getWeight(w1, w2, str) << endl;
    }
    return 0;
}