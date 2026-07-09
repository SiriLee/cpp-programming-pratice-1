# cpp_int / cpp_dec_float 速查

接口与 `int` / `double` 完全一致。

## 引入

```cpp
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/multiprecision/cpp_dec_float.hpp>
using namespace boost::multiprecision;
```

## cpp_int — 大整数

```cpp
cpp_int a("12345678901234567890");  // 巨数必须用字符串构造
cpp_int b = 42;                     // 小数字面量可以直接
string s = a.str();                 // 转字符串

// + - * / % << >>  < > <= == != 全部自然可用
cpp_int c = a + b * 3;
cpp_int q = a / b;   // 向零截断
int r = (int)(a % 2); // 取余（返回 cpp_int，强转 int）
gcd(a, b);  pow(a, 10);  sqrt(a);
cin >> a;   cout << a;
```

## cpp_dec_float — 大浮点数

```cpp
cpp_dec_float_100 x("123.456");  // 模板参数 = 有效位数
cpp_dec_float_100 y("0.789");
auto z = x + y;                  // + - * / 全部可用
cout << setprecision(50) << z;   // 控制输出精度
string s = z.str(20);            // 四舍五入到 20 位
```

## OJ 的 1014 / 1017 直接用 cpp_int

```cpp
// 1014: 大浮点数加法（保留 N 位小数）
cpp_dec_float_500 a(s1), b(s2);
cout << (a + b).str(N);

// 1017: 负二进制（直接除 -2）
while (n != 0) {
    int r = (int)(n % (-2));  if (r < 0) r += 2;
    n = (n - r) / (-2);
    collect r;
}

// 1012: 大整数加法
cpp_int a(s1), b(s2);  cout << a + b;
```
