#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// First 30 primes — enough for 25-digit inputs plus carry overflow
const int PRIMES[] = {2,   3,   5,   7,   11,  13,  17,  19,  23,  29,
                      31,  37,  41,  43,  47,  53,  59,  61,  67,  71,
                      73,  79,  83,  89,  97,  101, 103, 107, 109, 113};

// Parse a comma-separated prime-base number, return digits LSB-first
vector<int> parse(const string& s) {
  vector<int> digits;
  stringstream ss(s);
  string token;
  while (getline(ss, token, ',')) {
    digits.push_back(stoi(token));
  }
  reverse(digits.begin(), digits.end());
  return digits;
}

// Add two prime-base numbers (both LSB-first), return LSB-first result
vector<int> add(const vector<int>& a, const vector<int>& b) {
  vector<int> result;
  int carry = 0;
  int max_len = max(a.size(), b.size());

  for (int i = 0; i < max_len || carry > 0; i++) {
    int da = (i < (int)a.size()) ? a[i] : 0;
    int db = (i < (int)b.size()) ? b[i] : 0;
    int sum = da + db + carry;
    int base = PRIMES[i];
    result.push_back(sum % base);
    carry = sum / base;
  }

  return result;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int T;
  cin >> T;
  cin.ignore();  // consume newline after T

  for (int t = 0; t < T; t++) {
    string line;
    getline(cin, line);

    // Split "A B" by the space separator
    size_t space_pos = line.find(' ');
    string a_str = line.substr(0, space_pos);
    string b_str = line.substr(space_pos + 1);

    vector<int> a = parse(a_str);
    vector<int> b = parse(b_str);
    vector<int> result = add(a, b);

    cout << "case #" << t << ":\n";
    for (int i = (int)result.size() - 1; i >= 0; i--) {
      if (i < (int)result.size() - 1) cout << ',';
      cout << result[i];
    }
    cout << '\n';
  }

  return 0;
}
