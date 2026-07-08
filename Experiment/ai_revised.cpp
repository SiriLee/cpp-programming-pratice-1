/**
 * EOJ #1013 - Binary Reversal (Revised from AI-generated code)
 *
 * Problem: Given n (0 <= n <= 10^100), reverse its 334-bit binary
 * representation and output the resulting integer.
 *
 * Algorithm insight:
 *   "Divide by 2 and record remainders" naturally produces binary bits
 *   in LSB-first order — which is exactly the REVERSED order.
 *   So we don't need to explicitly reverse anything!
 *
 *   Step 1: Repeatedly divide the decimal string by 2, collecting
 *           remainders (0 or 1) — these are the reversed binary bits.
 *   Step 2: Multiply by 2 and add each bit to reconstruct the decimal
 *           value of the reversed binary number.
 *
 * Time  complexity: O(B * D), B=334 bits, D<=101 decimal digits
 * Space complexity: O(D + B), strings for decimal and binary
 */

#include <iostream>
#include <string>

// ---------------------------------------------------------------------------
// Divide a decimal string by 2.
// Returns the quotient string and sets `rem` to the remainder (0 or 1).
// Example: div2("123", rem) → quotient "61", rem = 1
// ---------------------------------------------------------------------------
std::string div2(const std::string& num, int& rem) {
    std::string quotient;
    quotient.reserve(num.size());

    int carry = 0;
    for (char c : num) {
        int cur = carry * 10 + (c - '0');
        quotient.push_back(static_cast<char>(cur / 2 + '0'));
        carry = cur % 2;          // carry is always 0 or 1 since divisor is 2
    }
    rem = carry;                   // final carry IS the remainder

    // Strip leading zeros from quotient
    std::size_t pos = quotient.find_first_not_of('0');
    return (pos == std::string::npos) ? "0" : quotient.substr(pos);
}

// ---------------------------------------------------------------------------
// Multiply a decimal string by 2, then add a single bit (0 or 1).
// Processes from right to left, propagating carries.
// Example: mul2add("5", 1) → "11"  (5*2 + 1 = 11)
// ---------------------------------------------------------------------------
std::string mul2add(const std::string& num, int bit) {
    std::string result = num;
    int carry = bit;               // start with the bit to add

    for (int i = static_cast<int>(result.size()) - 1; i >= 0; --i) {
        int cur = (result[i] - '0') * 2 + carry;
        result[i] = static_cast<char>(cur % 10 + '0');
        carry = cur / 10;
    }

    // If there's a final carry, prepend it
    if (carry > 0) {
        result.insert(result.begin(), static_cast<char>(carry + '0'));
    }
    return result;
}

// ---------------------------------------------------------------------------
// Strip leading zeros from a decimal string, preserving a single "0" if the
// number is zero.
// ---------------------------------------------------------------------------
std::string stripLeadingZeros(const std::string& s) {
    std::size_t pos = s.find_first_not_of('0');
    if (pos == std::string::npos) return "0";
    return (pos > 0) ? s.substr(pos) : s;
}

// ---------------------------------------------------------------------------
// Test helper: run the algorithm on a single input and return the result.
// Useful for unit testing edge cases.
// ---------------------------------------------------------------------------
std::string solveOne(const std::string& decimalInput) {
    // Step 0: Normalize input (remove leading zeros)
    std::string num = stripLeadingZeros(decimalInput);

    // Step 1: Decimal → reversed binary bits (LSB-first = already reversed!)
    std::string revBinary;
    revBinary.reserve(334);        // max 334 bits
    {
        std::string temp = num;
        while (temp != "0") {
            int rem;
            temp = div2(temp, rem);
            revBinary.push_back(static_cast<char>(rem + '0'));
        }
    }
    // Edge case: n = 0 → no bits collected → revBinary is empty → result = 0
    if (revBinary.empty()) {
        revBinary = "0";
    }

    // Step 2: Reversed binary → decimal (multiply by 2 and add each bit)
    std::string answer = "0";
    for (char bit : revBinary) {
        answer = mul2add(answer, bit - '0');
    }
    return answer;
}

// ---------------------------------------------------------------------------
// Main: read T test cases and output results in the required format.
// ---------------------------------------------------------------------------
int main() {
    // I/O optimization for competitive programming
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int T;
    std::cin >> T;

    for (int t = 0; t < T; ++t) {
        std::string N;
        std::cin >> N;

        std::string ans = solveOne(N);

        std::cout << "case #" << t << ":\n" << ans << "\n";
    }

    return 0;
}
