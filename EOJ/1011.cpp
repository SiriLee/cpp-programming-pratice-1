#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;
using ll = long long;

// 考点: Maya历日期排序
// 关键: 自定义格式解析(月份名→数字), 多关键字sort

static const unordered_map<string, int> month_map = {
    {"pop", 0}, {"no", 1}, {"zip", 2}, {"zotz", 3}, {"tzec", 4},
    {"xul", 5}, {"yoxkin", 6}, {"mol", 7}, {"chen", 8}, {"yax", 9},
    {"zac", 10}, {"ceh", 11}, {"mac", 12}, {"kankin", 13}, {"muan", 14},
    {"pax", 15}, {"koyab", 16}, {"cumhu", 17}, {"uayet", 18}
};

class MayaDate {
private:
    int day;
    string month;
    int year;
public:
    MayaDate() : day(0), month(""), year(0) {}
    MayaDate(int d, string m, int y) : day(d), month(m), year(y) {}
    string toString() const {
        return to_string(day) + ". " + month + " " + to_string(year);
    }
    bool operator<(const MayaDate& other) const {
        if (year != other.year) return year < other.year;
        if (month_map.at(month) != month_map.at(other.month)) 
            return month_map.at(month) < month_map.at(other.month);
        return day < other.day;
    }
};

int main() {
    int T; cin >> T;
    for (int t = 0; t < T; t++) {
        cout << "case #" << t << ":" << endl;
        int N; cin >> N;
        vector<MayaDate> dates;
        while (N--) {
            string d_str; string m; int y;
            cin >> d_str >> m >> y;
            int d = stoi(d_str.substr(0, d_str.size() - 1));
            MayaDate date(d, m, y);
            dates.push_back(date);
        }
        sort(dates.begin(), dates.end());
        for (const auto& date : dates) {
            cout << date.toString() << endl;
        }
    }
    return 0;
}