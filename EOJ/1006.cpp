#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

const int prime[25] = {
    2, 3, 5, 7, 11, 
    13, 17, 19, 23, 29, 
    31, 37, 41, 43, 47, 
    53, 59, 61, 67, 71, 
    73, 79, 83, 89, 97
};

vector<int> getNumArr(const string& str) {
    vector<int> numArr;
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
    return numArr;
}

ll strToNum(const string& str) {
    auto revArr = getNumArr(str);
    reverse(revArr.begin(), revArr.end());
    ll result = 0;
    ll weight = 1;
    for (int i = 0; i < revArr.size(); ++i) {
        result += revArr[i] * weight;
        weight *= prime[i];
    }
    return result;
}

string numToStr(ll num) {
    vector<int> numArr;
    for (int i = 0; i < 25 && num > 0; ++i) {
        numArr.push_back(num % prime[i]);
        num /= prime[i];
    }
    reverse(numArr.begin(), numArr.end());
    string result;
    for (int i = 0; i < numArr.size(); ++i) {
        result += to_string(numArr[i]) + ",";
    }
    result.pop_back();
    return result;
}

int main() {
    int T; cin >> T;
    for (int t = 0; t < T; ++t) {
        string A, B; cin >> A >> B;
        ll numA = strToNum(A);
        ll numB = strToNum(B);
        ll sum = numA + numB;
        cout << "case #" << t << ":" << endl;
        cout << numToStr(sum) << endl;
    }
    return 0;
}