#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int main() {
    int n; cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        int byteCount = 0;
        int oneCount = 0;
        char c;
        while (cin.get(c) && c != '\n') {
            oneCount += __builtin_popcount((unsigned char)c);
            ++byteCount;
        }
        int g = gcd(oneCount, byteCount * 8);
        cout << oneCount / g << "/" << byteCount * 8 / g << endl;
    }
    return 0;
}