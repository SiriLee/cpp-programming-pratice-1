#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

// 考点: 字串排序 (按字母频率+字典序重排)
// 关键: map统计频率, sort自定义比较

struct StrNum {
    string str;
    ll num;
    StrNum(string s) : str(s), num(-1) {
        string numStr;
        for (char c : s) {
            if (isdigit(c)) {
                numStr += c;
            }
        }
        if (!numStr.empty())
            num = stoll(numStr);
    }
    bool operator<(const StrNum& other) const {
        if (num != other.num) {
            return num < other.num;
        }
        return str < other.str;
    }
};

int main() {
    string str;
    vector<StrNum> vec;
    while (cin >> str) {
        vec.emplace_back(str);
    }
    sort(vec.begin(), vec.end());
    for (const auto& sn : vec) {
        cout << sn.str << ' ';
    }
    return 0;
}