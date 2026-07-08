#ifndef ALGO_H
#define ALGO_H

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

template<typename T>
T qpow(T a, ll n) {
    T res = 1;
    while (n) {
        if (n & 1) res = res * a;
        a = a * a;
        n >>= 1;
    }
    return res;
}

#endif
