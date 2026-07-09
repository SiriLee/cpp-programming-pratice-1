#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using ui = unsigned int;
using ull = unsigned long long;

// 考点: 素数进制A+B (混合进制加法)
// 关键: 每位基数不同(第i位基数为prime[i]), 进位至多1
// 参考: core/base_algo.md §4 混合进制

const ui prime[25] = {
    2, 3, 5, 7, 11, 
    13, 17, 19, 23, 29, 
    31, 37, 41, 43, 47, 
    53, 59, 61, 67, 71, 
    73, 79, 83, 89, 97
};

vector<ui> strToArr(const string& str) {
    vector<ui> numArr;
    string numStr;
    for (char c : str) {
        if (c == ',') {
            numArr.push_back(stoi(numStr));
            numStr.clear();
        } else {
            numStr += c;
        }
    }
    numArr.push_back(stoi(numStr));
    reverse(numArr.begin(), numArr.end());
    return numArr;
}

vector<ui> addNumArr(const vector<ui>& arrA, const vector<ui>& arrB) {
    vector<ui> result;
    ui carry = 0;
    int n = max(arrA.size(), arrB.size());
    for (int i = 0; i < n; ++i) {
        ui a = (i < arrA.size()) ? arrA[i] : 0;
        ui b = (i < arrB.size()) ? arrB[i] : 0;
        ui sum = a + b + carry;
        if (sum >= prime[i]) {
            carry = 1;
            sum -= prime[i];
        } else {
            carry = 0;
        }
        result.push_back(sum);
    }
    if (carry) {
        result.push_back(carry);
    }
    return result;
}

string arrToStr(vector<ui>& arr) {
    reverse(arr.begin(), arr.end());
    string result;
    for (ui num : arr) {
        result += to_string(num) + ",";
    }
    result.pop_back();
    return result;
}

int main() {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        string A, B; cin >> A >> B;
        auto numA = strToArr(A);
        auto numB = strToArr(B);
        auto sum = addNumArr(numA, numB);
        cout << "case #" << t << ":" << endl;
        cout << arrToStr(sum) << endl;
    }
    return 0;
}