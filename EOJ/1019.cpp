#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 字符分类统计 (字母/数字/空格/其他)
// 关键: isalpha/isdigit/isspace, 注意大小写统计

struct CharInfo {
    int lc;
    int uc;
    int dc;
    int sc;
    int oc;
    CharInfo() : lc(0), uc(0), dc(0), sc(0), oc(0) {}
    string toString() const {
        return to_string(uc) + " " + to_string(lc) + " " + to_string(sc) + 
        " " + to_string(dc) + " " + to_string(oc);
    }
};

CharInfo analyzeString(const string& s) {
    CharInfo info;
    for (char c : s) {
        if (islower(c)) info.lc++;
        else if (isupper(c)) info.uc++;
        else if (isdigit(c)) info.dc++;
        else if (isspace(c)) info.sc++;
        else info.oc++;
    }
    return info;
}

int main() {
    int T; cin >> T;
    cin.ignore();
    for (int t = 0; t < T; ++t) {
        string line; getline(cin, line);
        CharInfo info = analyzeString(line);
        cout << "case #" << t << ":" << endl;
        cout << info.toString() << endl;
    }
    return 0;
}