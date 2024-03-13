#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "number.h"
#include "function.h"

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

void reduce(struct NUMBER* N) {

    if (N->denominator_re == 0) { N->denominator_re = 1; N->numerator_re = 0; return; }
    char sign = 0;

    if ((double)N->denominator_re / N->numerator_re < 0) sign = 1;

    if (N->numerator_re < 0) N->numerator_re = -N->numerator_re;
    if (N->denominator_re < 0) N->denominator_re = -N->denominator_re;

    long long d = gcd(N->numerator_re, N->denominator_re);

    N->denominator_re /= d;
    N->numerator_re /= d;
    if (sign) N->numerator_re *= -1;



    if (N->denominator_im == 0) { N->denominator_im = 1; N->numerator_im = 0; return; }
    sign = 0;

    if ((double)N->denominator_im / N->numerator_im < 0) sign = 1;

    if (N->numerator_im < 0) N->numerator_im = -N->numerator_im;
    if (N->denominator_im < 0) N->denominator_im = -N->denominator_im;

    d = gcd(N->numerator_im, N->denominator_im);

    N->denominator_im /= d;
    N->numerator_im /= d;
    if (sign) N->numerator_im *= -1;
}

struct NUMBER add(struct NUMBER N1, struct NUMBER N2) {
    struct NUMBER ret;

    reduce(&N1);
    reduce(&N2);

    long long d_re = gcd(N1.denominator_re, N2.denominator_re);

    ret.denominator_re = N1.denominator_re * (N2.denominator_re / d_re);
    ret.numerator_re = (N1.numerator_re * (N2.denominator_re / d_re)) + (N2.numerator_re * (N1.denominator_re / d_re));

    long long d_im = gcd(N1.denominator_re, N2.denominator_re);

    ret.denominator_im = N1.denominator_im * (N2.denominator_im / d_im);
    ret.numerator_im = (N1.numerator_im * (N2.denominator_im / d_im)) + (N2.numerator_im * (N1.denominator_im / d_im));

    reduce(&ret);

    return ret;
}

struct NUMBER subtract(struct NUMBER N1, struct NUMBER N2) {
    struct NUMBER ret;

    reduce(&N1);
    reduce(&N2);

    long long d = gcd(N1.denominator_re, N2.denominator_re);

    ret.denominator_re = N1.denominator_re * (N2.denominator_re / d);
    ret.numerator_re = (N1.numerator_re * (N2.denominator_re / d)) - (N2.numerator_re * (N1.denominator_re / d));

    long long d_im = gcd(N1.denominator_re, N2.denominator_re);

    ret.denominator_im = N1.denominator_im * (N2.denominator_im / d);
    ret.numerator_im = (N1.numerator_im * (N2.denominator_im / d)) - (N2.numerator_im * (N1.denominator_im / d));

    reduce(&ret);

    return ret;
}

struct NUMBER multiply(struct NUMBER N1, struct NUMBER N2) {
    reduce(&N1);
    reduce(&N2);

    struct NUMBER re1 = { N1.numerator_re * N2.numerator_re, N1.denominator_re * N2.denominator_re, 0 , 1 };
    struct NUMBER re2 = { N1.numerator_im * N2.numerator_im, N1.denominator_im * N2.denominator_im, 0 , 1 };
    struct NUMBER re = subtract(re1, re2);

    struct NUMBER im1 = { 0, 1, N1.numerator_im * N2.numerator_re , N1.denominator_im * N2.denominator_re };
    struct NUMBER im2 = { 0, 1, N1.numerator_re * N2.numerator_im , N1.denominator_re * N2.denominator_im };
    struct NUMBER im = add(im1, im2);

    struct NUMBER ret = { re.numerator_re, re.denominator_re, im.numerator_im, im.denominator_im };

    reduce(&ret);

    return ret;
}

struct NUMBER divide(struct NUMBER N1, struct NUMBER N2) {
    reduce(&N1);
    reduce(&N2);

    N2.numerator_im *= -1;

    struct NUMBER num = multiply(N1, N2);

    struct NUMBER resqrd = { N2.numerator_re * N2.numerator_re, N2.denominator_re * N2.denominator_re, 0, 1 };
    struct NUMBER imsqrd = { N2.numerator_im * N2.numerator_im, N2.denominator_im * N2.denominator_im, 0, 1 };

    struct NUMBER dem = add(resqrd, imsqrd);

    struct NUMBER ret = { num.numerator_re * dem.denominator_re, num.denominator_re * dem.numerator_re, num.numerator_im * dem.denominator_re, num.denominator_im * dem.numerator_re };
    reduce(&ret);

    return ret;
}

void print_number(struct NUMBER* N) {
    if (N->numerator_re) {
        if (N->denominator_re != 1) printf("%lld/%lld", N->numerator_re, N->denominator_re);
        else printf("%lld", N->numerator_re);
    }
    if (N->numerator_re && N->numerator_im) printf(" + ");
    if (N->numerator_im) {
        if (N->denominator_im != 1) printf("%lld/%lld", N->numerator_im, N->denominator_im);
        else printf("%lld", N->numerator_im);
        printf(" i");
    }

    if (!N->numerator_re && !N->numerator_im) printf("0");


}