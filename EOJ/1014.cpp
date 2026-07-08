#include <iostream>
#include <vector>
#include <algorithm>
#include <list>

using namespace std;
using ll = long long;

string getSum(const string& A, const string& B, int N) {
    // Data produce
    list<int> a_list, b_list;
    int a_pre_len = 0, b_pre_len = 0;
    int a_post_len = 0, b_post_len = 0;
    int index = 0;
    for (char c : A) {
        if (c == '.') {
            a_pre_len = index;
            index = 0;
        } else {
            a_list.push_front(c);
            ++index;
        }
    }
    a_post_len = index;
    index = 0;
    for (char c : B) {
        if (c == '.') {
            b_pre_len = index;
            index = 0;
        } else {
            b_list.push_front(c - '0');
            ++index;
        }
    }
    b_post_len = index;

    int pre_len = max(a_pre_len, b_pre_len);
    int post_len = max(a_post_len, b_post_len);
    while (a_pre_len < pre_len) {
        a_list.push_back(0); ++a_pre_len;
    }
    while (b_pre_len < pre_len) {
        b_list.push_back(0); ++b_pre_len;
    }
    while (a_post_len < post_len) {
        a_list.push_front(0); ++a_post_len;
    }
    while (b_post_len < post_len) {
        b_list.push_front(0); ++b_post_len;
    }
    vector<int> a(a_list.begin(), a_list.end());
    vector<int> b(b_list.begin(), b_list.end());
    int n = max(a.size(), b.size());
    // add
    vector<int> result(n+1, 0);
    int carry = 0;
    for (int i = 0; i < n; ++i) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
    result[n] = carry;
    // put point
    string str;
    index = 0;
    int point_index = result.size() - post_len;
    for (auto it = result.rbegin(); it != result.rend(); ++it) {
        if (index == pre_len) {
            str.push_back('.');
        }
        str.push_back('0' + *it);
        ++index;
    }
    // fix
    index = 0;
    for (char c : str) {
        if (c != '0' || c == '.') break;
        ++index;
    }
    str.erase(str.begin(), str.begin() + index);
    if (str.front() == '.') str.insert(str.begin(), '0');
    int cur_post_len = post_len;
    while (cur_post_len < N) {
        result.push_back('0');
        ++cur_post_len;
    }
    index = 0;
    for (auto it = str.rbegin(); it != str.rend(); ++it) {
        if (index == post_len - N) break;
        ++index;
    }
    
    
}

int main() {
    string A, B; int N;
    cin >> A >> B >> N;
    cout << getSum(A, B, N) << endl;
    return 0;
}