# STL 考场速查

## 输入输出

```cpp
// 格式化浮点数（自动四舍五入）
cout << fixed << setprecision(N) << val;   // N 位小数
cout << setw(W) << setfill('0') << x;      // 宽度 W，前填充 '0'
```

## string

```cpp
// 大小写转换
transform(s.begin(), s.end(), s.begin(), ::toupper);  // 全大写
transform(s.begin(), s.end(), s.begin(), ::tolower);  // 全小写

// 字符串→数字（可指定进制）
int x = stoi("1A", nullptr, 16);   // = 26
ll y = stoll("12345678901");
double d = stod("3.14");

// 数字→字符串
string s = to_string(42);             // "42"

// 子串
string sub = s.substr(pos, len);      // 从 pos 起 len 个字符
string sub = s.substr(pos);           // 从 pos 到末尾

// 查找（返回 string::npos 表示没找到）
size_t p = s.find('x');               // 字符
size_t p = s.find("ab");              // 子串
size_t p = s.rfind('x');              // 从右往左找

// split
size_t pos = s.find('.');
if (pos != string::npos) {
    string first = s.substr(0, pos);
    string second = s.substr(pos + 1);
}
```

## sort 自定义比较

```cpp
// 默认 operator <
// 降序：greater<>()，或反向比较
sort(v.begin(), v.end(), greater<int>());
```

## 容器特殊用法

```cpp
// priority_queue 小顶堆（三个模板参数，第三个是 Compare）
priority_queue<int, vector<int>, greater<int>> pq;  // 小顶堆

// set 自定义比较（在类型里写死）
struct Cmp { bool operator()(int a, int b) const { return a > b; } };
set<int, Cmp> s;  // 降序 set

// map 按 value 排序（map 只能按 key 排）
vector<pair<K,V>> vec(m.begin(), m.end());
sort(vec.begin(), vec.end(),
    [](const auto& a, const auto& b) { return a.second < b.second; });
```

## algorithm 易忘函数

```cpp
// 去重（先排序，unique 只移动不删除）
sort(v.begin(), v.end());
v.erase(unique(v.begin(), v.end()), v.end());

// 二分查找（返回迭代器，减去 begin 得下标）
auto it = lower_bound(v.begin(), v.end(), x);  // 第一个 >= x
auto it = upper_bound(v.begin(), v.end(), x);  // 第一个 > x
int idx = it - v.begin();                       // 下标

// 全排列（必须从排序状态开始）
sort(v.begin(), v.end());
do { /* ... */ } while (next_permutation(v.begin(), v.end()));

// gcd / lcm（C++17）
ll g = gcd(a, b);
ll l = lcm(a, b);   // C++17

// 求和
ll sum = accumulate(v.begin(), v.end(), 0LL);  // 第三个参数决定返回类型
```

## stringstream

```cpp
// split 模板
string line; getline(cin, line);
stringstream ss(line);
string word;
while (ss >> word) { /* 处理每个 word */ }  // 遇空格自动分割

// 类型转换（可混合不同类型）
stringstream ss;
ss << 42 << ' ' << 3.14;
int a; double b; ss >> a >> b;
```