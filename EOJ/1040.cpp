#include <iostream>
#include <fstream>
#include <string>
#include <regex>

using namespace std;

string remove_comments(const string& code) {
    string result;
    regex block_re(R"(/\*[\s\S]*?\*/|"(?:\\.|[^"\\])*"|'(?:\\.|[^\'\\])*')");
    regex line_re(R"(//.*)");
    istringstream stream(code);
    string line;
    bool in_block_comment = false;
    while (getline(stream, line)) {
        string processed_line = line;
        if (in_block_comment) {
            smatch m;
            if (regex_search(processed_line, m, regex(R"(\*/)"))) {
                processed_line = m.suffix().str();
                in_block_comment = false;
            } else {
                processed_line = "";
            }
        }
        if (!in_block_comment && !processed_line.empty()) {
            processed_line = regex_replace(processed_line, line_re, "");
            result += processed_line + "\n";
        } else if (in_block_comment) {
            result += "\n";
        }
    }
    return result;
}

int main() {
    string text, line;
    while (getline(cin, line)) {
        text += line + "\n";
    }
    cout << remove_comments(text);
}