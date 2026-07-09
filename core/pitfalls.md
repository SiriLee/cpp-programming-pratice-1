# 易错陷阱

- **`cin>>` 后 `getline`**：换行符残留 → `cin.ignore()`
- **`%` 负号**：`-5 % 2 = -1`，负进制须 `if (r < 0) r += abs(R)`
- **`cpp_int("050")`**：前导零被当八进制 → 先去零
- **`cpp_dec_float<N>` 表达式**：不能直接 `.str()` → 先赋值
- **`accumulate` 返回类型**：由第三个参数决定 → 写 `0LL`
- **`unique`**：只移不删 → `v.erase(unique(...), v.end())`
- **`next_permutation`**：从当前状态开始 → 先 `sort`
- **01背包 `j` 倒序**，完全背包正序
- **`substr(pos, len)`**：`len` 是长度，不是结束下标
- **`gcd(0,0)=0`**：约分前检查
- **`double` 不能 `==`**：`abs(a-b) < 1e-9`
- **`::toupper`**：不加 `::` 编译错误（`<locale>` 模板冲突）
