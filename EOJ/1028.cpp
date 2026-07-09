#include <bits/stdc++.h>

using namespace std;
using ll = long long;

// 考点: 莫尔斯电码解码
// 关键: unordered_map查表, '/'个数(3=空格, 5=句号)

static const unordered_map<string, char> codes = {
    {".-", 'A'}, {"-...", 'B'}, {"-.-.", 'C'}, {"-..", 'D'}, {".", 'E'}, {"..-.", 'F'},
    {"--.", 'G'}, {"....", 'H'}, {"..", 'I'}, {".---", 'J'}, {"-.-", 'K'},
    {".-..", 'L'}, {"--", 'M'}, {"-.", 'N'}, {"---", 'O'}, {".--.", 'P'},
    {"--.-", 'Q'}, {".-.", 'R'}, {"...", 'S'}, {"-", 'T'}, {"..-", 'U'},
    {"...-", 'V'}, {".--", 'W'}, {"-..-", 'X'}, {"-.--", 'Y'}, {"--..", 'Z'}, 
    {"-----", '0'}, {".----", '1'}, {"..---", '2'}, {"...--", '3'}, {"....-", '4'}, 
    {".....", '5'}, {"-....", '6'}, {"--...", '7'}, {"---..", '8'}, {"----.", '9'}
};

string parse(const string& text) {
    int LCnt = 0;
    string word;
    string info;
    for (char c : text) {
        if (c == '/') {
            if (!word.empty()) {
                info += codes.at(word);
                word.clear();
            }
            if (LCnt == 5) {
                info += "."; LCnt = 0;
            }
            ++LCnt;
        } else {
            if (LCnt != 0) {
                if (LCnt == 3) {
                    info += " ";
                } else if (LCnt == 5) {
                    info += ".";
                }
                LCnt = 0;
            }
            word += c;
        }
    }
    if (!word.empty()) info += codes.at(word);
    if (LCnt != 0) {
        if (LCnt == 3) {
            info += " ";
        } else if (LCnt == 5) {
            info += ".";
        }
    }
    return info;
}

int main() {
    int T; cin >> T;
    for (int i = 0; i < T; ++i) {
        string text; cin >> text;
        cout << "case #" << i << ":\n";
        cout << parse(text);
        cout << "\n";
    }
    return 0;
}