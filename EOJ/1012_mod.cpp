#include <bits/stdc++.h>

using namespace std;
using ll = long long;

struct BigInt {
    string v;
    BigInt(const string& s = "0");

    
}

int main() {
    string A, B;
    while (cin >> A >> B) {
        string sum = function(A, B);
        cout << sum << endl;
    }
    return 0;
}