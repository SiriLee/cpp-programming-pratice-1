#include <bits/stdc++.h>

using namespace std;
using ll = long long;

string opposite(const string& s) {
    string res;
    for (char c : s) {
        if (c == '0') res += '1';
        else res += '0';
    }
    return res;
}

string generate(int n) {
    string res = "0";
    while (n--) {
        res += opposite(res);
    }
    return res;
}

int main() {
    int i; cin >> i;
    cout << generate(i) << endl;
    return 0;
}