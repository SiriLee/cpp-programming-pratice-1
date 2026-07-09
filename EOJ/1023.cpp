#include <bits/stdc++.h>

using namespace std;
using ll = long long;

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