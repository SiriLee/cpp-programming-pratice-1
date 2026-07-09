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

## 01背包

```cpp
// M容量, w重量, v价值 —— 每个物品最多选一次
vector<ll> dp(M + 1);
for (int i = 0; i < n; ++i)
    for (int j = M; j >= w[i]; --j)          // 倒序！倒序！倒序！
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
// 答案: dp[M]
```

```cpp
// 完全背包（每件物品无限次）—— 循环正序即可
for (int i = 0; i < n; ++i)
    for (int j = w[i]; j <= M; ++j)          // 正序
        dp[j] = max(dp[j], dp[j - w[i]] + v[i]);
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

## 质数相关

```cpp
// 试除法判质数（O(√n)，单次查询够用）
bool isPrime(ll n) {
    if (n < 2) return false;
    for (ll i = 2; i * i <= n; ++i)
        if (n % i == 0) return false;
    return true;
}

// 前 k 个质数表（筛法，k 不太大时直接用）
vector<int> primes;
for (int i = 2; primes.size() < k; ++i) {
    bool ok = true;
    for (int p : primes) {
        if (p * p > i) break;
        if (i % p == 0) { ok = false; break; }
    }
    if (ok) primes.push_back(i);
}
```
