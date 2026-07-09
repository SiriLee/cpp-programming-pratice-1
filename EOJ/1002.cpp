#include <iostream>
#include <utility>
#include <string>
#include <algorithm>

using namespace std;
using ll = long long;

// 考点: R进制→最简代分数 (integer + proper fraction)
// 关键: 整数部分与小数部分分别处理, gcd约分, 分母恒正
// 易错: gcd 注意符号

string table = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

// 整数部分
ll rToInt(const string& s, int R) {
    ll result = 0;
    for (char c : s) {
        int digit;
        digit = (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10);
        result = result * R + digit;
    }
    return result;
}

// 最简代分数
pair<ll, ll> rToFraction(const string& s, int R) {
    ll numerator = 0;
    ll denominator = 1;
    for (char c : s) {
        ll digit;
        digit = (c >= '0' && c <= '9') ? (c - '0') : (c - 'A' + 10);
        numerator = numerator * R + digit;
        denominator *= R;
    }
    // 约分
    ll gcd = __gcd(numerator, denominator);
    numerator /= gcd;
    denominator /= gcd;
    return {numerator, denominator};    
}

int main() {
    int R; string input;
    cin >> R >> input;
    if (input.front() == '-') {
        cout << "-";
        input = input.substr(1);
    }
    size_t dotPos = input.find('.');
    string intPart = (dotPos == string::npos) ? input : input.substr(0, dotPos);
    ll intValue = rToInt(intPart, R);
    auto fracPart = rToFraction((dotPos == string::npos) ? "" : input.substr(dotPos + 1), R);
    if (fracPart.first == 0) {
        cout << intValue << endl;
    } else {
        if (intValue == 0) {
            cout << fracPart.first << " " << fracPart.second << endl;
        } else {
            cout << intValue << " " << fracPart.first << " " << fracPart.second << endl;
        }
    }
    return 0;
}