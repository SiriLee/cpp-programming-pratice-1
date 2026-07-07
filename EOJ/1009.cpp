#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

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