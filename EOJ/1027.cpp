#include <bits/stdc++.h>

using namespace std;
using ll = long long;

bool isSplit(char c) {
    return c == ' ' || c == ',' || c == '.' || c == '!' || c == '?';
}

set<string> getWords(const string text) {
    set<string> words;
    string word;
    for (char c : text) {
        if (isSplit(c)) {
            if (!word.empty()) words.insert(word);
            word.clear();
            continue;
        }
        word += tolower(c);
    }
    if (!word.empty()) words.insert(word);
    return words;
}

int main() {
    int T; cin >> T; cin.ignore();
    for (int i = 0; i < T; ++i) {
        string text;
        getline(cin, text);
        cout << "case #" << i << ":\n";
        auto words = getWords(text);
        bool isFirst = true;
        for (const auto& word : words) {
            if (!isFirst) cout << " ";
            else isFirst = false;
            cout << word;
        }
        cout << "\n";
    }
    return 0;
}