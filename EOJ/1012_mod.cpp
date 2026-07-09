#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>

using namespace std;
using namespace boost::multiprecision;
using ll = long long;

int main() {
    cpp_int A, B;
    while (cin >> A >> B) {
        cpp_int result = A + B;
        cout << result << endl;
    }
    return 0;
}