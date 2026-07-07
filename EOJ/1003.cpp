#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
using ll = long long;

ll getMinNum(const string& str) {
    vector<int> arr;
    unordered_map<char, int> map;
    int R = 0;
    for (char c : str) {
        if (map.find(c) == map.end()) {
            int digit = R > 1 ? R : (R == 1 ? 0 : 1);
            arr.push_back(digit);
            map[c] = digit;
            ++R;
        } else {
            arr.push_back(map[c]);
        }
    }
    int base = max(2, (int)map.size());
    ll result = 0;
    for (int d : arr) {
        result = result * base + d;
    }
    return result;
}

int main() {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        string str; cin >> str;
        cout << "case #" << t << ":\n" << getMinNum(str) << endl;
    }
    return 0;
}