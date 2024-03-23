#include "Headers.h"

struct Int128 int128_0 = { 0, 0 };
struct Int128 int128_1 = { 0, 1 };

struct SCALAR s0 = { 0, 1 };

unsigned long long gcd(long long a, long long b) {

    if (a < b) { long long temp = a; a = b; b = temp; }
    if (a == 0) return b;
    if (b == 0) return a;

    // Find the greatest power of 2 that divides both a and b
    unsigned long long shift;
    for (shift = 0; ((a | b) & 1) == 0; ++shift) {
        a >>= 1;
        b >>= 1;
    }

    // Remove any remaining factors of 2 from a
    while ((a & 1) == 0) {
        a >>= 1;
    }

    // Binary GCD algorithm
    do {
        // Remove any remaining factors of 2 from b
        while ((b & 1) == 0) {
            b >>= 1;
        }

        // Now a and b are both odd, so compute their absolute difference
        if (a > b) {
            unsigned long long temp = a;
            a = b;
            b = temp;
        }
        b = b - a;
    } while (b != 0);

    // Restore the common power of 2
    return a << shift;
}

double SCALAR_to_double(struct SCALAR* x) {
    reduce(x);
    return (double)x->numerator / x->denominator;

}

struct SCALAR double_to_SCALAR(double d) {
    long long intpart = (long long)d;
    double decpart = d - intpart;
    struct SCALAR intnum = { intpart, 1 };
    struct SCALAR decnum = {(long long)(8316000000000000000 * decpart), 8316000000000000000 };
    struct SCALAR ret = add_SCALAR(intnum, decnum);
    reduce_NUMBER(&ret);
   // ret = round_SCALAR(&ret, 3);
    return ret;
}

struct NUMBER double_to_NUMBER(double d) {
    struct NUMBER ret = { s0, s0 };
    long long intpart = (long long) d;
    double decpart = d - intpart;
    struct NUMBER intnum = { { intpart, 1 }, s0 };
    struct NUMBER decnum = { {(long long) (8316000000000000000 * decpart), 8316000000000000000 }, s0 };
    ret = add_NUMBER(intnum, decnum);
    reduce_NUMBER(&ret);
    ret.re = round_SCALAR(&ret.re, 3);
    return ret;
}

struct NUMBER String_to_NUMBER(char* number, int base) {
    struct NUMBER ret = { s0, s0 };
    int i = 0;
    if (number[0] == '-') i++;
    while (number[i] != '.' && number[i] != 0) {
        ret.re.numerator *= base;
        ret.re.numerator += (number[i] - 48);
        i++;
    }
    i++;
    while (number[i] != 0)
    {
        ret.re.numerator *= base;
        ret.re.denominator *= base;
        ret.re.numerator += (number[i] - 48);
        i++;
    }
    if (number[0] == '-') ret.re.numerator *= -1;
    reduce_NUMBER(&ret);
    return ret;
}