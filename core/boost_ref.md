# cpp_int / cpp_dec_float 速查

考试 OJ 系统支持 Boost.Multiprecision！用它的话之前的 BigInt 大部分可省。

## 引入

```cpp
#include <boost/multiprecision/cpp_int.hpp>    // 大整数
#include <boost/multiprecision/cpp_dec_float.hpp> // 大浮点数
using namespace boost::multiprecision;
```

## cpp_int — 大整数

### 构造与 I/O

```cpp
cpp_int a("12345678901234567890");  // 从字符串
cpp_int b = 42;                     // 从整数字面量
string s = a.str();                 // 转字符串

cin >> a;  cout << a;              // 直接流输入输出
```

### 四则运算（自然运算符）

```cpp
cpp_int c = a + b;
cpp_int d = a - b;
cpp_int e = a * b;
cpp_int q = a / b;   // 向零截断（C++ 语义）
cpp_int r = a % b;   // 余数跟随被除数符号
```

### 比较

```cpp
if (a < b) ...
if (a == cpp_int("0")) ...
```

### 位运算、gcd、pow

```cpp
cpp_int x = a << 10;              // 左移
cpp_int y = a & 0xFF;             // 按位与
cpp_int z = gcd(a, b);            // 最大公约数
cpp_int p = pow(a, 100);          // 幂（整数指数）
cpp_int m = a % b;                // 取模
cpp_int s = sqrt(a);              // 整数平方根（向下取整）
```

### 负二进制转换示例（直接除 -2）

```cpp
string dec_to_neg2(cpp_int n) {
    if (n == 0) return "0";
    string res;
    while (n != 0) {
        cpp_int q = n / (-2);     // / 向零截断
        int r = (int)(n % (-2));   // % 余数跟随被除数
        if (r < 0) { r += 2; q += 1; }
        res += (r + '0');
        n = q;
    }
    reverse(res.begin(), res.end());
    return res;
}
```

对比自己写的 BigInt：不需要自己实现任何算法，`/ -2` 直接就能除，`+` 直接就能加。

---

## cpp_dec_float — 大浮点数

```cpp
#include <boost/multiprecision/cpp_dec_float.hpp>
using namespace boost::multiprecision;

// 模板参数：有效数字位数（十进制）
cpp_dec_float_100 a("123456789.123456789123456789");
cpp_dec_float_100 b("0.000000000000000001");

cpp_dec_float_100 c = a + b;
cout << setprecision(50) << c << endl;  // 控制输出精度

// 转字符串
string s = c.str(20);  // 保留 20 位小数
```

### 四舍五入到 N 位小数（1014 替换方案）

```cpp
string add_float(const string& a, const string& b, int prec) {
    cpp_dec_float_500 x(a), y(b);   // 500 位有效数字，够用
    cpp_dec_float_500 z = x + y;
    // 四舍五入到 prec 位：加 0.5×10^(-prec) 然后截断
    cpp_dec_float_500 half("0.5");
    for (int i = 0; i < prec; ++i) half /= 10;
    z = z + (z >= 0 ? half : -half);
    string s = z.str(prec);
    // str(prec) 直接截断，需补整数位的小数点
    if (s.find('.') == string::npos) s += ".";
    s = s.substr(0, s.find('.') + prec + 1);
    return s;
}
```

实际上 cpp_dec_float 的 `str(prec)` 已经做四舍五入了，一般直接 `.str(N)` 即可。

---

## 类型速查

| 类型 | 用途 | 示例 |
|------|------|------|
| `cpp_int` | 任意精度整数 | 默认 |
| `int128_t` | 128 位有符号 | `int128_t` |
| `uint256_t` | 256 位无符号 | `uint256_t` |
| `int512_t` | 512 位有符号 | `int512_t` |
| `int1024_t` | 1024 位有符号 | `int1024_t` |
| `cpp_dec_float_50` | 50 位有效数字浮点 | 可选任意位数 |
| `cpp_dec_float_100` | 100 位 | 同上 |
| `cpp_dec_float_500` | 500 位 | 500 位可靠 |

固定宽度类型（int128_t 等）比 cpp_int 快，位数已知时优先用。
