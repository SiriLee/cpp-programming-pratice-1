#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace std;
using namespace boost::multiprecision;
using ll = long long;
using bf = number<cpp_dec_float<500>>;


int main() {
    string s1, s2; int M, N;
    cin >> s1 >> s2 >> M >> N;
    bf A(s1); bf B(s2);
    if (M == 1) {
        bf R = A + B;
        cout << fixed << setprecision(N) << R;
    } else {
        bf R = A - B;
        cout << fixed << setprecision(N) << R;
    }
    return 0;
}