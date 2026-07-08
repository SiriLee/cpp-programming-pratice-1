#include "big_int.h"
#include "big_float.h"
#include "parser.h"
#include <cassert>
#include <iostream>

int main() {
    int ok = 0, fail = 0;
#define T(cond, msg) do { if (!(cond)) { cerr << "FAIL: " << msg << endl; ++fail; } else ++ok; } while(0)

    // ===== BigInt =====
    {
        BigInt z, a("123"), b("456"), c("0"), d("00123");
        T(z.s == "0", "BigInt default");
        T(c.s == "0", "BigInt 0");
        T(d.s == "123", "BigInt strip0");
        T(BigInt(42LL).s == "42", "BigInt from ll");

        T(cmp(a, b) < 0, "cmp a<b");
        T(cmp(b, a) > 0, "cmp b>a");
        T(cmp(a, BigInt("123")) == 0, "cmp eq");
        T(cmp(a, b) < 0 && cmp(b, a) > 0, "rel ops");
        T(cmp(a, BigInt("123")) == 0 && cmp(a, b) != 0, "eq/ne");

        T((a + b).s == "579", "add");
        T((BigInt("999") + BigInt("1")).s == "1000", "add carry");
        T((a - BigInt("23")).s == "100", "sub");
        T((BigInt("1000") - BigInt("1")).s == "999", "sub borrow");
        T((BigInt("5") - BigInt("5")).s == "0", "sub to 0");
        T((BigInt("12") * BigInt("34")).s == "408", "mul");
        T((BigInt("99") * BigInt("99")).s == "9801", "mul 99");
        T((BigInt("0") * BigInt("999")).s == "0", "mul by 0");

        auto [q1, r1] = div_by_int(BigInt("0"), 2);
        T(q1.s == "0" && r1 == 0, "div 0");
        auto [q2, r2] = div_by_int(BigInt("123"), 2);
        T(q2.s == "61" && r2 == 1, "div 123/2");
        auto [q3, r3] = div_by_int(BigInt("255"), 16);
        T(q3.s == "15" && r3 == 15, "div 255/16");

        string s = "000123";
        BigInt::strip0(s);           T(s == "123", "strip0");
    }

    // ===== BigFloat =====
    {
        // add
        T(add_bigfloat("0.5", "0.5", 1) == "1.0", "fadd 0.5+0.5");
        T(add_bigfloat("0.99", "0.01", 2) == "1.00", "fadd 0.99+0.01");
        T(add_bigfloat("1.25", "2.75", 2) == "4.00", "fadd 1.25+2.75");
        T(add_bigfloat("0", "0.5", 1) == "0.5", "fadd 0+0.5");
        T(add_bigfloat("123.456", "0.544", 3) == "124.000", "fadd 3prec");
        T(add_bigfloat("999.999", "0.001", 3) == "1000.000", "fadd big carry");
        // rounding
        T(add_bigfloat("0.995", "0.001", 2) == "1.00", "fadd round up");
        T(add_bigfloat("0.994", "0.001", 2) == "1.00", "fadd round up .5");
        T(add_bigfloat("0.990", "0.004", 2) == "0.99", "fadd no round");
        T(add_bigfloat("1.005", "0.000", 2) == "1.01", "fadd round 1.005");
        // prec=0
        T(add_bigfloat("1.5", "2.3", 0) == "4", "fadd prec=0 round up");
        T(add_bigfloat("1.2", "2.3", 0) == "4", "fadd prec=0 round down");

        // sub
        T(sub_bigfloat("1.0", "0.5", 1) == "0.5", "fsub 1.0-0.5");
        T(sub_bigfloat("2.3", "1.54", 2) == "0.76", "fsub 2.3-1.54");
        T(sub_bigfloat("0.5", "0.5", 1) == "0.0", "fsub same");
        T(sub_bigfloat("100.0", "0.001", 3) == "99.999", "fsub borrow");
        T(sub_bigfloat("100.000", "0.001", 2) == "100.00", "fsub round");
        T(sub_bigfloat("0.5", "1.0", 1) == "-0.5", "fsub a<b");
        T(sub_bigfloat("1.54", "2.3", 2) == "-0.76", "fsub a<b round");
    }

    // ===== Parser small int =====
    {
        T(str_to_ll("0", 10) == 0, "stoll 0");
        T(str_to_ll("FF", 16) == 255, "stoll FF");
        T(str_to_ll("1010", 2) == 10, "stoll bin");
        T(str_to_ll("ZZ", 36) == 35*36+35, "stoll ZZ");

        T(ll_to_str(0, 10) == "0", "lltos 0");
        T(ll_to_str(255, 16) == "FF", "lltos FF");
        T(ll_to_str(10, 2) == "1010", "lltos bin");
        T(ll_to_str(-10, 10) == "-10", "lltos neg");
        T(ll_to_str(35*36+35, 36) == "ZZ", "lltos ZZ");

        // round-trip
        for (int R = 2; R <= 36; ++R)
            for (ll x : {0LL, 1LL, 12345LL, 999999LL, -100LL}) {
                T(str_to_ll(ll_to_str(x, R), R) == x,
                  ("roundtrip R=" + to_string(R) + " x=" + to_string(x)).c_str());
            }
    }

    // ===== Parser fraction & float =====
    {
        auto [n1, d1] = str_to_fraction("1010.101", 2);
        T(n1 == 85 && d1 == 8, "frac 1010.101b = 85/8");  // 10.625
        auto [n2, d2] = str_to_fraction("F.8", 16);
        T(n2 == 248 && d2 == 16, "frac F.8 = 248/16");    // 15.5
        auto [n3, d3] = str_to_fraction("1.2", 10);
        T(n3 == 12 && d3 == 10, "frac 1.2 = 12/10");
        auto [n4, d4] = str_to_fraction("42", 10);
        T(n4 == 42 && d4 == 1, "frac int");

        T(abs(str_to_double("1010.101", 2) - 10.625) < 1e-9, "stod bin");
        T(abs(str_to_double("F.8", 16) - 15.5) < 1e-9, "stod hex");

        T(double_to_str(10.625, 2, 3) == "1010.101", "dtos bin");
        T(double_to_str(15.5, 16, 1) == "F.8", "dtos hex");
        T(double_to_str(-1.5, 10, 1) == "-1.5", "dtos neg");
    }

    // ===== Parser big int =====
    {
        T(str_to_dec("0", 2) == "0", "big stod 0");
        T(str_to_dec("1010", 2) == "10", "big stod bin");
        T(str_to_dec("FF", 16) == "255", "big stod hex");

        T(dec_to_str("0", 2) == "0", "big dtos 0");
        T(dec_to_str("10", 2) == "1010", "big dtos bin");
        T(dec_to_str("255", 16) == "FF", "big dtos hex");

        // big round-trip
        for (int R : {2, 8, 10, 16, 36}) {
            string x = "12345678901234567890";
            T(str_to_dec(dec_to_str(x, R), R) == x,
              ("big roundtrip R=" + to_string(R)).c_str());
        }
        // 2^64-1
        T(str_to_dec("1111111111111111111111111111111111111111111111111111111111111111", 2)
          == "18446744073709551615", "big bin 64 ones");
        T(dec_to_str("18446744073709551615", 2)
          == "1111111111111111111111111111111111111111111111111111111111111111", "big dec->bin");
    }

    cout << ok << " passed, " << fail << " failed" << endl;
    return fail ? 1 : 0;
}
