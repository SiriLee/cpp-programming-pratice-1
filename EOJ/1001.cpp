#include <iostream>

using namespace std;
using ll = long long;

string table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

string intToR(ll a, int R) {
    if (a == 0) return "0";
    string s = "";
    while (a > 0) {
        int r = a % R;
        s = table[r] + s;
        a /= R;
    }
    return s;
}

ll rToInt(const string& s, int R) {
    ll result = 0;
    for (char c : s) {
        int digit;
        if (c >= '0' && c <= '9') {
            digit = c - '0';
        } else if (c >= 'A' && c <= 'Z') {
            digit = c - 'A' + 10;
        } else {
            digit = c - 'a' + 10;
        }
        result = result * R + digit;
    }
    return result;
}

int main() {
    int A, B; string num;
    cin >> A >> num >> B;
    ll num_10 = rToInt(num, A);
    string result = intToR(num_10, B);
    cout << result << endl;
    return 0;
}