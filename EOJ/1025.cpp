#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 最长无重复子串
// 关键: 滑动窗口 + unordered_map<char,int> 记录最后出现位置
// 参考: core/templates.md 滑动窗口

string longestUniqSubStr(const string& str) {
    map<int, pair<int, int>> len_map; // len - (s, e)
    unordered_map<char, int> map; // ch - index
    int start = 0, end = 0;
    while (true) {
        int len = 0;
        unordered_map<char, int> new_map;
        for (int i = start; i <= end; ++i) {
            new_map[str[i]] = i;
            ++len;
        }
        map = new_map;
        while (end < str.size()) {
            if (++end == str.size()) break;
            char c = str[end];
            if (map.find(c) == map.end()) {
                map[c] = end;
                ++len;
            } else {
                if (len_map.find(len) == len_map.end()) 
                    len_map[len] = {start, end};
                start = map[c] + 1;
                break;
            }
        }
        if (end == str.size()) {
            if (len_map.find(len) == len_map.end())
                len_map[len] = {start, end};
            break;
        }
    }
    auto range = (*len_map.rbegin()).second;
    string sub_str = str.substr(range.first, range.second - range.first);
    return sub_str;
}

int main() {
    string str; cin >> str;
    cout << longestUniqSubStr(str) << endl;
    return 0;
}