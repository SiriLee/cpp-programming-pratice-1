#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;
using ll = long long;

string dec_to_neg2(cpp_int& n) {
    if (n == 0) return "0";
    string res;
    while (n != 0) {
        int r = (int)(n % -2);
        n /= -2;
        if (r < 0) {
            r += 2;
            n += 1;
        }
        res = char('0' + r) + res;
    }
    return res;
}

int main() {
    cpp_int n;
    cin >> n;
    cout << dec_to_neg2(n) << endl;
    return 0;
}