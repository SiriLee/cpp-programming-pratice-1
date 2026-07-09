# cpp_int / cpp_dec_float 速查

接口与 `int` / `double` 完全一致。

## 引入

```cpp
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
using namespace boost::multiprecision;
```

---

## cpp_int — 大整数（直接可用）

```cpp
cpp_int a("12345678901234567890");  // 巨数：字符串构造
cpp_int b = 42;                     // 小数：直接赋值
string s = a.str();                 // 转字符串

// + - * / %  < > <= == !=  >> <<  全部自然
cpp_int c = a + b * 3;
cpp_int q = a / b;                  // 向零截断
int r = (int)(a % 2);              // 取余，强转 int
gcd(a, b);  pow(a, 10);  sqrt(a);
cin >> a;   cout << a;             // 直接 I/O
```

表达式返回值可以直接用，不需要显式类型转换。

---

## cpp_dec_float — 大浮点数

### 预定义类型（直接可用，位数固定）

```cpp
cpp_dec_float_50  x("1.5");   //  50 位有效数字
cpp_dec_float_100 y("2.5");   // 100 位
cpp_dec_float_100 z = x + y;  // 表达式可直接赋值
cout << z.str(20);             // 保留 20 位小数，四舍五入
```

### 自定义位数（用 `number<>` 模板，1014 用这）

```cpp
number<cpp_dec_float<500>> p("123.456");  // 500 位
number<cpp_dec_float<500>> q("0.789");
number<cpp_dec_float<500>> r = p + q;      // 表达式必须显式转
cout << r.str(N);                           // 保留 N 位，四舍五入
```

**不能直接** `cpp_dec_float<500> p("...")` — 裸后端不认字符串。  
**不能直接** `(p + q).str(N)` — 表达式模板没有 `.str()`。

---

## OJ 常用写法

```cpp
// 1012: 大整数加减
cpp_int a(s1), b(s2);  cout << a + b;

// 1014: 大浮点数加法，保留 N 位（用 fixed + setprecision）
using BF = number<cpp_dec_float<500>>;
BF a(sa), b(sb);  BF c = a + b;
stringstream ss; ss << fixed << setprecision(N) << c; cout << ss.str();

// 1017: 负二进制（cpp_int 直接除 -2）
cpp_int n(dec);
string res;
while (n != 0) {
    int r = (int)(n % (-2));  if (r < 0) r += 2;
    n = (n - r) / (-2);
    res += (r + '0');
}
reverse(res.begin(), res.end());
```
