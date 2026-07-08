#include "big_num.h"
#include "parser.h"
#include <cassert>
#include <iostream>

#define T(cond, msg) do { if (!(cond)) { cerr << "FAIL: " << msg << endl; fail++; } else ok++; } while(0)

int main() {
    int ok = 0, fail = 0;

    // ===== cmp_bigint =====
    T(cmp_bigint("0", "0") == 0, "cmp 0==0");
    T(cmp_bigint("123", "99") == 1, "cmp 123>99");
    T(cmp_bigint("99", "123") == -1, "cmp 99<123");
    T(cmp_bigint("00123", "123") == 0, "cmp leading zeros");
    T(cmp_bigint("100", "100") == 0, "cmp 100==100");

    // ===== add_bigint =====
    T(add_bigint("0", "0") == "0", "add 0+0");
    T(add_bigint("123", "456") == "579", "add 123+456");
    T(add_bigint("999", "1") == "1000", "add carry");
    T(add_bigint("99999999999999999999", "1") == "100000000000000000000", "add big carry");

    // ===== sub_bigint =====
    T(sub_bigint("100", "10") == "90", "sub 100-10");
    T(sub_bigint("100", "100") == "0", "sub same");
    T(sub_bigint("1000", "1") == "999", "sub borrow chain");
    T(sub_bigint("5", "5") == "0", "sub 5-5");
    T(sub_bigint("123456789", "123456788") == "1", "sub 1");

    // ===== mul_bigint =====
    T(mul_bigint("0", "123") == "0", "mul by 0");
    T(mul_bigint("123", "0") == "0", "mul 0");
    T(mul_bigint("12", "34") == "408", "mul 12*34");
    T(mul_bigint("99", "99") == "9801", "mul 99*99");
    T(mul_bigint("999", "999") == "998001", "mul 999*999");
    T(mul_bigint("123456789", "987654321") == "121932631112635269", "mul big");

    // ===== div_bigint_by_int =====
    auto [q1, r1] = div_bigint_by_int("0", 2);
    T(q1 == "0" && r1 == 0, "div 0/2");
    auto [q2, r2] = div_bigint_by_int("123", 2);
    T(q2 == "61" && r2 == 1, "div 123/2");
    auto [q3, r3] = div_bigint_by_int("100", 3);
    T(q3 == "33" && r3 == 1, "div 100/3");
    auto [q4, r4] = div_bigint_by_int("255", 16);
    T(q4 == "15" && r4 == 15, "div 255/16");
    auto [q5, r5] = div_bigint_by_int("7", 2);
    T(q5 == "3" && r5 == 1, "div 7/2");

    // ===== add_bigfloat =====
    T(add_bigfloat("0.5", "0.5") == "1.0", "fadd 0.5+0.5");
    T(add_bigfloat("0.99", "0.01") == "1.00", "fadd 0.99+0.01");
    T(add_bigfloat("1.25", "2.75") == "4.00", "fadd 1.25+2.75");
    T(add_bigfloat("0", "0.5") == "0.5", "fadd 0+0.5");
    T(add_bigfloat("123.456", "0.544") == "124.000", "fadd 123.456+0.544");
    T(add_bigfloat("999.999", "0.001") == "1000.000", "fadd 999.999+0.001");

    // ===== sub_bigfloat =====
    T(sub_bigfloat("1.0", "0.5") == "0.5", "fsub 1.0-0.5");
    T(sub_bigfloat("2.3", "1.54") == "0.76", "fsub 2.3-1.54");
    T(sub_bigfloat("0.5", "0.5") == "0.0", "fsub same");
    T(sub_bigfloat("100.0", "0.001") == "99.999", "fsub 100.0-0.001");

    // ===== str_to_ll =====
    T(str_to_ll("0", 10) == 0, "str_to_ll 0");
    T(str_to_ll("FF", 16) == 255, "str_to_ll FF");
    T(str_to_ll("1010", 2) == 10, "str_to_ll 1010b");
    T(str_to_ll("ZZ", 36) == 35*36+35, "str_to_ll ZZ");

    // ===== ll_to_str =====
    T(ll_to_str(0, 10) == "0", "ll_to_str 0");
    T(ll_to_str(255, 16) == "FF", "ll_to_str 255->FF");
    T(ll_to_str(10, 2) == "1010", "ll_to_str 10->1010b");
    T(ll_to_str(-10, 10) == "-10", "ll_to_str neg");
    T(ll_to_str(35*36+35, 36) == "ZZ", "ll_to_str ZZ");

    // ===== round-trip small int =====
    for (int R = 2; R <= 36; ++R) {
        for (ll x : {0LL, 1LL, 12345LL, 999999LL}) {
            string s = ll_to_str(x, R);
            ll y = str_to_ll(s, R);
            T(x == y, ("roundtrip R=" + to_string(R) + " x=" + to_string(x)).c_str());
        }
    }

    // ===== str_to_double =====
    T(abs(str_to_double("1010.101", 2) - 10.625) < 1e-9, "str_to_double bin");
    T(abs(str_to_double("F.8", 16) - 15.5) < 1e-9, "str_to_double hex");

    // ===== double_to_str =====
    T(double_to_str(10.625, 2, 3) == "1010.101", "double_to_str bin");
    T(double_to_str(15.5, 16, 1) == "F.8", "double_to_str hex");
    T(double_to_str(-1.5, 10, 1) == "-1.5", "double_to_str neg");

    // ===== str_to_dec (big) =====
    T(str_to_dec("0", 2) == "0", "str_to_dec 0");
    T(str_to_dec("1010", 2) == "10", "str_to_dec 1010b");
    T(str_to_dec("FF", 16) == "255", "str_to_dec FF");
    T(str_to_dec("1111111111111111111111111111111111111111111111111111111111111111", 2)
      == "18446744073709551615", "str_to_dec 64bit max");  // 2^64 - 1

    // ===== dec_to_str (big) =====
    T(dec_to_str("0", 2) == "0", "dec_to_str 0");
    T(dec_to_str("10", 2) == "1010", "dec_to_str 10b");
    T(dec_to_str("255", 16) == "FF", "dec_to_str 255h");
    T(dec_to_str("18446744073709551615", 2)
      == "1111111111111111111111111111111111111111111111111111111111111111", "dec_to_str big bin");

    // ===== round-trip big int =====
    for (int R : {2, 8, 10, 16, 36}) {
        string s = "12345678901234567890";
        string dec = str_to_dec(s, 10);  // already decimal
        T(dec == s, "str_to_dec identity");
        string enc = dec_to_str(dec, R);
        string dec2 = str_to_dec(enc, R);
        T(dec2 == dec, ("big roundtrip R=" + to_string(R)).c_str());
    }

    // ===== big_num round-trip: mul then div =====
    {
        string a = "12345678901234567890";
        string b = "98765432109876543210";
        string prod = mul_bigint(a, b);
        auto [q, r] = div_bigint_by_int(prod, 3);
        T(mul_bigint(q, "3") == sub_bigint(prod, to_string(r)), "mul-div check");
    }

    cout << ok << " passed, " << fail << " failed" << endl;
    return fail ? 1 : 0;
}
