# 题型模板

## 分数化简与加法

```cpp
struct Frac {
    ll p, q;  // p/q
    Frac(ll a = 0, ll b = 1) : p(a), q(b) { reduce(); }
    void reduce() {
        if (q < 0) p = -p, q = -q;         // 分母恒正
        ll g = gcd(abs(p), q);
        if (g) p /= g, q /= g;
    }
};
Frac operator+(const Frac& a, const Frac& b) {
    return Frac(a.p * b.q + b.p * a.q, a.q * b.q);
}
```

## 背包问题

```cpp
// 01背包：每件物品至多一次，求最大价值
vector<ll> dp(M + 1);
for (int i = 0; i < n; ++i)
    for (int j = M; j >= w[i]; --j)          // 倒序
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
// 答案: dp[M]
```

```cpp
// 完全背包：每件物品无限次 —— 仅循环正序，其余相同
for (int i = 0; i < n; ++i)
    for (int j = w[i]; j <= M; ++j)          // 正序
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
```

```cpp
// 子集和 / 精准匹配：能否选出若干物品恰好装满 M（bool dp）
vector<bool> dp(M + 1);
dp[0] = true;
for (int w : weights)
    for (int j = M; j >= w; --j)             // 01 倒序；完全则正序
        dp[j] = dp[j] || dp[j - w];
// 答案: dp[M] 为 true 表示可以
```

```cpp
// 天平称重：每个砝码可放左(+w)、放右(-w) 或不选（1031）
// dp[j+offset] 表示能否称出重量 j（j 可为负）
int sum = accumulate(w.begin(), w.end(), 0);
vector<bool> dp(2 * sum + 1);
dp[sum] = true;                              // offset = sum
for (int wi : w) {
    vector<bool> ndp(2 * sum + 1);
    for (int j = 0; j <= 2 * sum; ++j) {
        if (!dp[j]) continue;
        ndp[j] = true;                       // 不选
        if (j >= wi) ndp[j - wi] = true;     // 放右边（负）
        if (j + wi <= 2 * sum) ndp[j + wi] = true; // 放左边（正）
    }
    dp = move(ndp);
}
// 答案：遍历 dp[sum+1 .. 2*sum] 中所有 true 的 j-sum
```

## 滑动窗口（最长无重复子串）

```cpp
// 返回最长不重复子串长度
int l = 0, ans = 0;
unordered_map<char, int> pos;                // 字符→最后出现位置
for (int r = 0; r < s.size(); ++r) {
    if (pos.count(s[r])) l = max(l, pos[s[r]] + 1);
    pos[s[r]] = r;
    ans = max(ans, r - l + 1);
}
// 如需返回子串本身：s.substr(l, r-l+1) 在 ans 更新时记录
```

## 括号匹配

```cpp
// basic: 判断是否合法
stack<char> st;
for (char c : s) {
    if (c == '(') st.push(c);
    else {
        if (st.empty()) return false;
        st.pop();
    }
}
return st.empty();
```

```cpp
// 嵌套深度（或类似计分）
int depth = 0, score = 0;
for (char c : s) {
    if (c == '(') ++depth;
    else { --depth; score += (1 << depth); }  // 每层贡献 2^depth
}
```

## DFS 回溯（字符串/组合枚举）

```cpp
// 枚举所有长度为 n、由字母集 chars 组成的字符串
void dfs(string& cur, const string& chars, int n) {
    if (cur.size() == n) { /* 处理 cur */ return; }
    for (char c : chars) {
        cur.push_back(c);
        dfs(cur, chars, n);
        cur.pop_back();                       // 回溯
    }
}
```
