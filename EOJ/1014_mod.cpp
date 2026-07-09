#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace std;
using namespace boost::multiprecision;
using ll = long long;

int main() {
    string sa, sb; int N; cin >> sa >> sb >> N;
    number<cpp_dec_float<500>> a(sa), b(sb);
    number<cpp_dec_float<500>> c = a + b;
    cout << c.str(N);
    return 0;
}
