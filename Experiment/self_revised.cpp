/**
 * EOJ #1013 - Binary Reversal
 * self_revised.cpp — my hand-written code, revised after debugging & review.
 *
 * Changes from self_initial.cpp:
 *   1. Replaced <bits/stdc++.h> with <iostream>/<string>/<vector> (portability).
 *   2. Fixed the n=0 bug — in v1, find_last_not_of('0') returned npos,
 *      causing erase(npos+1) = UB. Now I simply skip the trim for n=0.
 *   3. Moved the reversal into decStrToBinary. I realized the division loop
 *      naturally produces LSB-first bits, which IS the reversed binary.
 *      The old approach (MSB-first → reverse → trim) was fighting this
 *      natural property rather than using it.
 *   4. Used size_t in addBigInt to fix the signedness mismatch Cppcheck warned about.
 *   5. Replaced the confusing rbegin/rend char→int construction in addBigInt
 *      with an explicit manual loop that does c - '0' upfront.
 *   6. Removed unused 'using ll = long long'.
 *   7. Dropped the artificial 334-iteration limit — the loop now runs only
 *      as many times as needed (until the number reduces to 0).
 *
 * Things I kept from my original style (different from the AI version):
 *   - vector<int> for digit storage during division. I find it more
 *     explicit than operating directly on strings.
 *   - >>1 and &1 for /2 and %2. Not faster here, but it's a habit from
 *     reading systems-level code — and it reminds me these are bit ops.
 *   - addBigInt reused from my EOJ #1012 solution. Could have written a
 *     dedicated mul2add like the AI did, but reusing tested code felt safer.
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ---------------------------------------------------------------------------
// Convert decimal string → binary bits, LSB first (= already reversed).
//
// How it works: repeatedly divide the big number by 2, recording each
// remainder. Because we extract the LSB first, the output string is the
// binary in reverse order — exactly what the problem asks for.
//
// Example: "10" → divisions produce remainders 0,1,0,1 → "0101"
//          This IS the reverse of binary "1010".
// ---------------------------------------------------------------------------
string decStrToBinary(const string& num) {
    // Work with individual decimal digits (0-9) in a vector
    vector<int> digits;
    digits.reserve(num.size());
    for (char c : num) {
        digits.push_back(c - '0');
    }

    string bits;
    // At most 334 bits for 10^100, but we stop early when number hits 0
    bits.reserve(340);

    while (true) {
        // Current number's parity → next bit (LSB first)
        bits.push_back(static_cast<char>((digits.back() & 1) + '0'));

        // Divide the whole number by 2 (simulated long division)
        vector<int> quotient;
        quotient.reserve(digits.size());
        int rem = 0;

        for (int d : digits) {
            int cur = rem * 10 + d;
            // Skip leading zeros in quotient (same as hand division:
            // 0123 ÷ 2, we write "61" not "061")
            if (!quotient.empty() || (cur >> 1) != 0) {
                quotient.push_back(cur >> 1);
            }
            rem = cur & 1;
        }

        if (quotient.empty()) break;   // number fully reduced to 0
        digits = move(quotient);
    }

    return bits;
}

// ---------------------------------------------------------------------------
// Add two non-negative decimal strings, return the sum as a string.
// Reused and cleaned up from my EOJ #1012 solution.
// ---------------------------------------------------------------------------
string addBigInt(const string& A, const string& B) {
    // Store digits in reverse (units at index 0) for easy carry propagation.
    // Explicitly convert each char to int — the old version used rbegin/rend
    // iterators which implicitly cast char→int (ASCII value), requiring a
    // later -'0' fixup. This version is more obviously correct.
    vector<int> a, b;
    a.reserve(A.size());
    b.reserve(B.size());
    for (int i = static_cast<int>(A.size()) - 1; i >= 0; --i) a.push_back(A[i] - '0');
    for (int i = static_cast<int>(B.size()) - 1; i >= 0; --i) b.push_back(B[i] - '0');

    size_t n = max(a.size(), b.size());
    a.resize(n, 0);
    b.resize(n, 0);

    vector<int> result(n + 1, 0);
    int carry = 0;
    for (size_t i = 0; i < n; ++i) {
        int sum = a[i] + b[i] + carry;
        result[i] = sum % 10;
        carry = sum / 10;
    }
    result[n] = carry;

    // Build result string (most significant digit first), skip leading zeros
    string res;
    for (int i = static_cast<int>(result.size()) - 1; i >= 0; --i) {
        if (res.empty() && result[i] == 0) continue;
        res.push_back(static_cast<char>(result[i] + '0'));
    }
    return res.empty() ? "0" : res;
}

// ---------------------------------------------------------------------------
// Convert binary string (MSB first) → decimal string.
// Uses double-and-add: for each bit b, ans = ans * 2 + b.
// I implement *2 as ans + ans since I already have addBigInt.
// ---------------------------------------------------------------------------
string binaryToDecStr(const string& binary) {
    string result = "0";
    for (char c : binary) {
        string doubled = addBigInt(result, result);     // result * 2
        result = addBigInt(doubled, string(1, c));      // + current bit
    }
    return result;
}

// ---------------------------------------------------------------------------
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;

    for (int t = 0; t < T; ++t) {
        string num;
        cin >> num;

        // decStrToBinary returns LSB-first bits.
        // Since the problem reverses the binary, and LSB-first IS the reversed
        // order, we can feed this directly to binaryToDecStr (which interprets
        // the first bit as MSB of the reversed number).
        string revBin = decStrToBinary(num);

        // Leading zeros in revBin are harmless — binaryToDecStr starting from
        // "0" means 0*2+0=0 repeatedly until a '1' appears. No need to trim.
        // But we must handle the case where revBin is empty (shouldn't happen
        // since decStrToBinary always produces at least one bit).
        string ans = binaryToDecStr(revBin);

        cout << "case #" << t << ":\n" << ans << "\n";
    }

    return 0;
}
