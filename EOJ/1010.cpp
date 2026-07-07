#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using ll = long long;

class email {
private:
    string name;
    string domain;
public:
    email() = default;
    email(const string& email_str) {
        auto at_pos = email_str.find('@');
        name = email_str.substr(0, at_pos);
        domain = email_str.substr(at_pos + 1);
    }

    bool operator<(const email& other) const {
        if (domain != other.domain) {
            return domain < other.domain;
        }
        return name > other.name;
    }

    friend ostream& operator<<(ostream& os, const email& e) {
        os << e.name << "@" << e.domain;
        return os;
    }
};



int main() {
    int n; cin >> n;
    vector<email> emails(n);
    for (int i = 0; i < n; ++i) {
        string email_str; cin >> email_str;
        emails[i] = email(email_str);
    }
    sort(emails.begin(), emails.end());
    for (const auto& e : emails) {
        cout << e << endl;
    }
    return 0;
}