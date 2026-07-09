#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bool isSpecialWord(const string& word) {
    return word == "the" || word == "a" || word == "an" || word == "of" || word == "for" || word == "and";
}

int getWordsCount(const string& line) {
    int count = 0;
    stringstream ss(line);
    string word;
    while (ss >> word) {
        if (!isSpecialWord(word)) {
            ++count;
        }
    }
    return count;
}

int main() {
    int T; cin >> T; cin.ignore();
    for (int t = 0; t < T; ++t) {
        string line; getline(cin, line);
        cout << "case #" << t << ":" << endl;
        cout << getWordsCount(line) << endl;
    }
    return 0;
}