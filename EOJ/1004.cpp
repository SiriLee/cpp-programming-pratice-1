#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

string byteToHex(unsigned char byte) {
    const char hexDigits[] = "0123456789abcdef";
    string hex;
    hex += hexDigits[(byte >> 4) & 0x0F];
    hex += hexDigits[byte & 0x0F];
    return hex;
}

void printBytes(int data) {
    unsigned char* p = (unsigned char*)&data;
    for (int i = 0; i < sizeof(int); ++i) {
        cout << byteToHex(p[i]) << " ";
    }
    cout << endl;
}

void printBytes(double data) {
    unsigned char* p = (unsigned char*)&data;
    for (int i = 0; i < sizeof(double); ++i) {
        cout << byteToHex(p[i]) << " ";
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