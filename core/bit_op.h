#ifndef BIT_OP_H
#define BIT_OP_H
// 字节/位操作速查（开卷备查）

#include <bits/stdc++.h>
using namespace std;

// ---- 位计数 ----
inline int popcnt(unsigned int x)   { return __builtin_popcount(x); }     // 32位
inline int popcnt(unsigned long long x) { return __builtin_popcountll(x); } // 64位

// ---- 单字节 → 十六进制字符串 ----
inline string byte2hex(unsigned char c) {
    const char t[] = "0123456789abcdef";
    return {t[c >> 4], t[c & 0xF]};
}

// ---- 打印任意类型的底层字节（小端序） ----
template<typename T>
void print_bytes(const T& val) {
    auto* p = (const unsigned char*)&val;
    for (size_t i = 0; i < sizeof(T); ++i)
        cout << byte2hex(p[i]) << ' ';
    cout << '\n';
}

// ---- 字节序互换 ----
inline uint16_t bswap16(uint16_t x) { return (x >> 8) | (x << 8); }
inline uint32_t bswap32(uint32_t x) {
    x = ((x >> 8) & 0x00FF00FF) | ((x << 8) & 0xFF00FF00);
    return (x >> 16) | (x << 16);
}

// ---- 单比特操作 ----
inline bool test_bit(int x, int k)  { return (x >> k) & 1; }   // 读第 k 位
inline int  set_bit(int x, int k)   { return x | (1 << k); }   // 置 1
inline int  clear_bit(int x, int k) { return x & ~(1 << k); }  // 清 0
inline int  flip_bit(int x, int k)  { return x ^ (1 << k); }   // 翻转
inline int  lowbit(int x)           { return x & -x; }         // 取最低位 1（树状数组核心）

// ---- 字节截取 ----
inline int byte_k(int x, int k) { return (x >> (k * 8)) & 0xFF; } // 取第 k 个字节（小端，k=0 最低位）

#endif
