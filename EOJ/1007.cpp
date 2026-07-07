#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <tuple>
#include <numeric>

using namespace std;
using ll = long long;

int D(char c) {
    if (c == '0') return 0;
    if (c == '1') return 1;
    return -1;
}

ll parseInt(const string& s) {
    ll result = 0;
    for (char c : s) {
        result = result * 3 + D(c);
    }
    return result;
}

pair<ll, ll> parseFrac(const string& s) {
    ll num = 0, denom = 1;
    for (char c : s) {
        num = num * 3 + D(c);
        denom *= 3;
    }
    ll gcd = std::gcd(num, denom);
    return {num / gcd, denom / gcd};
}

tuple<ll, ll, ll> parse(const string& s) {
    auto pos = s.find('.');
    if (pos == string::npos) {
        return {parseInt(s), 0, 1};
    }
    ll integer = parseInt(s.substr(0, pos));
    auto p = parseFrac(s.substr(pos + 1));
    ll num = p.first;
    ll denom = p.second;
    // calculate the total number
    ll sumNum = integer * denom + num;
    ll totalInteger = sumNum / denom;
    ll temp = sumNum % denom;
    ll totalNum = totalInteger < 0 ? -temp : temp;
    return {totalInteger, totalNum, denom};
}

string toString(ll integer, ll num, ll denom) {
    if (num == 0) {
        return to_string(integer); // A
    }
    if (integer == 0) {
        return to_string(num) + " " + to_string(denom); // B C
    }
    return to_string(integer) + " " + to_string(num) + " " + to_string(denom); // A B C
}

int main() {
    string str; cin >> str;
    auto tp = parse(str);
    ll integer = get<0>(tp);
    ll num = get<1>(tp);
    ll denom = get<2>(tp);
    cout << toString(integer, num, denom) << endl;
    return 0;
}