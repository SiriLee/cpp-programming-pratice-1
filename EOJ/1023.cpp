#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 统计满足约束的字符串个数
// 关键: DFS回溯枚举所有组合, 用set自动去重排序
// 参考: core/templates.md DFS回溯

class StringGenerator {
public:
    StringGenerator(int n) : n_(n) {}
    int getResults();
private:
    int n_;
    vector<string> results_;
    void dfs(const string& cur, char c);
};

int StringGenerator::getResults() {
    dfs("", '1');
    dfs("", '0');
    return results_.size();
}

// no 101
void StringGenerator::dfs(const string& cur, char c) {
    if (cur.size() == n_ - 1) {
        results_.push_back(cur + c);
        return;
    }
    string new_cur = cur + c;
    char prev = cur.empty() ? '0' : cur.back();
    if (prev == '0' || c == '1') {
        dfs(new_cur, '1');
    }
    dfs(move(new_cur), '0');
}

int main() {
    int n;
    while (cin >> n) {
        if (n == -1) break;
        StringGenerator generator(n);
        cout << generator.getResults() << endl;
    }
    return 0;
}