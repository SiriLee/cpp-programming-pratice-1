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

// ---- 质数 ----

inline bool is_prime(ll n) {
    if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (ll i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0) return false;
    return true;
}

#endif
