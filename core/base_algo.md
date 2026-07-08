# 特殊进制速查

## 核心公式

```
n = q × R + r       其中 r ∈ 该进制合法数字集合
```

---

## → 十进制（Horner，高位到低位）

```cpp
// 标准进制
ll res = 0;
for (char c : s) {
    int d = isdigit(c) ? c - '0' : c - 'A' + 10;
    res = res * R + d;
}

// 混合进制（每位基数不同，R[i] 为第 i 位权重比）
ll res = 0;
for (int i = 0; i < n; ++i)
    res = res * R[i] + val[i];
```

## ← 十进制转出（短除 + 校正，低位到高位）

框架（四种变体通用）：

```cpp
string res;
while (n != 0) {
    int r = n % abs(R);            // 取 |R| 下的余数（C++ 中 % 符号跟随被除数）
    if (r < 0) r += abs(R);        // 确保非负
    if (r > max_digit) r -= abs(R); // 校正到合法范围（平衡进制）
    n = (n - r) / R;
    res += d[r];                   // d[r] 为数值 r 对应的字符
}
reverse(res.begin(), res.end());
```

---

## 四种变体

### 1. 标准进制（R > 0，数字 [0, R-1]）

```cpp
string ll_to_R(ll n, int R) {
    if (n == 0) return "0";
    string res;
    while (n) {
        int r = n % R;             // 天然在 [0, R-1]，无需校正
        res += (r < 10 ? r + '0' : r - 10 + 'A');
        n /= R;
    }
    reverse(res.begin(), res.end());
    return res;
}
```

### 2. 负进制（R < 0，数字 [0, |R|-1]）

```cpp
// 例: R = -2  →  EOJ 1017
string dec_to_negR(ll n, int R) {  // R 为负数，如 -2
    if (n == 0) return "0";
    string res;
    while (n) {
        int r = n % -R;            // % |R|, 如 % 2。C++ 中 n 可正可负
        if (r < 0) r += -R;        // 确保非负
        // 此时 r ∈ [0, |R|-1], 已合法
        n = (n - r) / R;           // R 为负, 注意 (n-r) 能被 R 整除
        res += (r + '0');
    }
    reverse(res.begin(), res.end());
    return res;
}
```

### 3. 平衡进制（数字以 0 为中心对称）

```cpp
// 例: 平衡三进制 (R=3, digits: -1/0/1)  →  EOJ 1007
string dec_to_balanced(ll n, int R) {
    if (n == 0) return "0";
    string res;
    while (n) {
        int r = n % R;             // C++: r ∈ [-(R-1), R-1]
        if (r > R / 2)  r -= R;   // 往负方向校正, 如 2→-1 (R=3)
        if (r < -R / 2) r += R;   // 往正方向校正
        n = (n - r) / R;
        // 按约定映射符号, 如平衡三进制: -1→'2', 0→'0', 1→'1'
        res += (r == -1 ? '2' : r + '0');
    }
    reverse(res.begin(), res.end());
    return res;
}
```

### 4. 混合进制（每位基数不同）

```cpp
// 例: 质数进制 (2,3,5,7,11,...)  →  EOJ 1006
// R[i] 为第 i 位（从低位起）的基数
vector<int> dec_to_mixed(ll n, const vector<int>& R) {
    vector<int> res;
    for (int i = 0; n; ++i) {
        int r = n % R[i];
        res.push_back(r);
        n /= R[i];
    }
    return res;  // res[0] 为最低位
}
```

---

## 考场上遇到新进制

1. **识别数字集** — 每个符号代表什么数值？最小值、最大值？
2. **确定基数 R 或 R[i]** — 相邻位权重比
3. **→ 十** — `res = res * R + val(d)`, 恒成立
4. **← 十** — 短除框架：`r = n % |R|` → 校正到合法区间 → `n = (n - r) / R`
5. **验证** — 最小的几个数手算一遍
