#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;
using ll = long long;

int getOneCount(char c) {
    int count = 0;
    char hide = 1;
    for (int i = 0; i < 8; ++i) {
        if (c & hide) {
            ++count;
        }
        hide <<= 1;
    }
    return count;
}

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

int main() {
    int n; cin >> n;
    cin.ignore();
    for (int i = 0; i < n; ++i) {
        int byteCount = 0;
        int oneCount = 0;
        char c;
        while (cin.get(c) && c != '\n') {
            oneCount += getOneCount(c);
            ++byteCount;
        }
        int g = gcd(oneCount, byteCount * 8);
        cout << oneCount / g << "/" << byteCount * 8 / g << endl;
    }
    return 0;
}