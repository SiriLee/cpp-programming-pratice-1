#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

// 考点: 内存字节逐字节打印(十六进制)
// 关键: 区分int(4字节)与double(8字节), 小端序
// 参考: core/bit_op.h byte2hex

inline string byte2hex(unsigned char c) {
    const char t[] = "0123456789abcdef";
    return {t[c >> 4], t[c & 0xF]};
}

void printBytes(int data) {
    unsigned char* p = (unsigned char*)&data;
    for (int i = 0; i < sizeof(int); ++i) {
        cout << byte2hex(p[i]) << " ";
    }
    cout << endl;
}

void printBytes(double data) {
    unsigned char* p = (unsigned char*)&data;
    for (int i = 0; i < sizeof(double); ++i) {
        cout << byte2hex(p[i]) << " ";
    }
    cout << endl;
}

int main() {
    string str;
    while (cin >> str) {
        int intData; double doubleDta;
        if (str.find(".") != string::npos) {
            doubleDta = stod(str);
            printBytes(doubleDta);
        } else {
            intData = stoi(str);
            printBytes(intData);
        }
    }
    return 0;
}