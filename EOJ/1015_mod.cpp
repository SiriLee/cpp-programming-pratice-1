#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_dec_float.hpp>

using namespace std;
using namespace boost::multiprecision;
using ll = long long;
using BF = number<cpp_dec_float<500>>;


int main() {
    string A, B; int N;
    cin >> A >> B >> N;
    BF a(A), b(B);
    BF c = a - b;
    stringstream ss; ss << fixed << setprecision(N) << c;
    cout << ss.str();
    return 0;
}