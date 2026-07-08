#ifndef BIG_INT_H
#define BIG_INT_H

#include <bits/stdc++.h>
using namespace std;
using ll = long long;

struct BigInt {
    string v;  // normalized: no leading zeros, "0" for zero

    BigInt(const string& s = "0");
    BigInt(ll n) : BigInt(to_string(n)) {}

    string str() const { return v; }

    static void strip0(string& s);
};

int cmp(const BigInt& a, const BigInt& b);
BigInt operator+(const BigInt& a, const BigInt& b);
BigInt operator-(const BigInt& a, const BigInt& b);  // a >= b
BigInt operator*(const BigInt& a, const BigInt& b);
pair<BigInt, int> div_by_int(const BigInt& a, int d);  // d in [2,36]
ostream& operator<<(ostream& os, const BigInt& a);

#endif
