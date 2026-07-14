#include <bits/stdc++.h>

using namespace std;
using ll = long long;

int getMinLen(const vector<string>& text, unordered_map<string, int>& words) {
    int n = text.size(); int m = words.size();
    int start = 0, end = 0;
    // Init start and end. [s, e)
    for (int cnt = 0; end < n && cnt < m; ++end) {
        string word = text[end];
        if (words.find(word) == words.end()) continue;
        ++words[word];
        if (words[word] == 1) ++cnt;
    }
    int minLen = end - start;
    // Move start and end to find the minimum length
    while (end < n) {
        minLen = min(minLen, end - start);
        string word = text[start];
        if (words.find(word) == words.end()) {
            ++start; continue;
        }
        if (words[word] > 1) {
            --words[word]; ++start; continue;
        }
        // words[word] == 1
        while (end < n) {
            if (words.find(text[end]) == words.end()) {
                ++end; continue;
            }
            if (text[end] == word) {
                ++start; ++end; break;
            }
            ++words[text[end]]; ++end;
        }
    }
    while (start < n) {
        string word = text[start];
        if (words.find(word) == words.end()) {
            ++start; continue;
        }
        if (words[word] > 1) {
            --words[word]; ++start; continue;
        }
        break;
    }
    minLen = min(minLen, end - start);
    return minLen;
}

int main() {
    int n; cin >> n;
    unordered_set<string> orin_words;
    for (int i = 0; i < n; ++i) {
        string word; cin >> word;
        orin_words.insert(word);
    }
    int m; cin >> m;
    vector<string> text(m);
    unordered_map<string, int> words; // word - count
    for (int i = 0; i < m; ++i) {
        cin >> text[i]; string word = text[i];
        if (orin_words.find(word) != orin_words.end() &&
         words.find(word) == words.end()) {
            words[word] = 0;
        }
    }
    cout << words.size() << endl;
    cout << getMinLen(text, words) << endl;
    return 0;
}