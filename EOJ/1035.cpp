#include <bits/stdc++.h>

using namespace std;
using ll = long long;

//{, , , }
void printVec(const vector<ll>& vec) {
    cout << "{";
    for (size_t i = 0; i < vec.size(); ++i) {
        cout << vec[i];
        if (i != vec.size() - 1) cout << ",";
    }
    cout << "}" << endl;
}

int main() {
    int A_cnt, B_cnt;
    cin >> A_cnt >> B_cnt;
    set<ll> A, B;
    for (int i = 0; i < A_cnt; ++i) {
        ll a; cin >> a;
        A.insert(a);
    }
    for (int i = 0; i < B_cnt; ++i) {
        ll b; cin >> b;
        B.insert(b);
    }
    vector<ll> C, D, E;
    set_intersection(A.begin(), A.end(), B.begin(), B.end(), back_inserter(C));
    set_union(A.begin(), A.end(), B.begin(), B.end(), back_inserter(D));
    set_difference(A.begin(), A.end(), B.begin(), B.end(), back_inserter(E));

    printVec(C);
    printVec(D);
    printVec(E);

    return 0;
}