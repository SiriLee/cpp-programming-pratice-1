# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## 项目概述

C++ OJ（Online Judge）机考备考仓库。`core/` 是自建代码库（开卷速查），`EOJ/` 是历史真题解答。

## 构建与测试

单文件编译，无构建系统：
```bash
g++ -std=c++17 -o prog EOJ/1001.cpp && ./prog
```

运行 core 全部测试：
```bash
g++ -std=c++17 -o core/test_all core/test_all.cpp core/big_float.cpp core/parser.cpp && ./core/test_all
```

## 编码风格

- `#include <bits/stdc++.h>` + `using namespace std;` 开头（OJ 风格）
- `using ll = long long;` 每个文件独立声明
- 注释精简，函数/变量名自解释
- 手写代码与库函数择一，不混用

## core/ 模块

| 文件 | 用途 | 特殊约定 |
|------|------|---------|
| `big_int.h` | BigInt（大整数 + - * div floor）| 单头文件，搜 `[NEG]` 可去掉负数支持 |
| `big_float.h/.cpp` | 大浮点数加减（精度+四舍五入）| |
| `parser.h/.cpp` | 进制转换 2~36（小整数/大整数/分数）| 搜 `[NEG]` 去掉负数支持 |
| `algo.h` | 通用快速幂 `qpow<T>(a, n)` | |
| `bit_op.h` | 位/字节操作速查（popcnt/byte2hex/bit/bswap）| |
| `base_algo.md` | 特殊进制算法速查（标准/负/平衡/混合）| 伪代码+真代码 |
| `boost_ref.md` | Boost.Multiprecision 速查（`cpp_int`/`cpp_dec_float`）| OJ系统支持Boost |

### BigInt 关键约定

- **floor 除法语义**：`div_by_int` 余数始终 ∈ [0, d-1]，商向负无穷取整（与 Python `//` 一致），非 C++ 的向零截断
- **非负默认**：`BigInt` 设计为非负，`[NEG]` 标记的代码是可选负数扩展。搜索 `[NEG]` 定位所有负数相关代码
- **成员**：`string s` 直接访问，无 getter
- 运算符不支持负数，仅 `div_by_int` 有 `[NEG]` 扩展

### Boost.Multiprecision（OJ支持时优先用）

- `cpp_int`：直接可用，接口与 `int` 完全一致
- `cpp_dec_float`：必须用 `number<cpp_dec_float<N>>` 包装，表达式结果需显式转换后才能调 `.str()`
- 输出固定 N 位小数用 `cout << fixed << setprecision(N)`，不用 `.str(N)`

## EOJ/ 真题

文件名对应题号（如 `1001.cpp`）。题目描述有时见 `EOJ/tasks/` 下的 `.txt` 文件。`*_mod.cpp` 是备选实现。
