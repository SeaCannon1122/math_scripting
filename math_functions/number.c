#include "Headers.h"

struct NUMBER combine(struct Int128* num_re, struct Int128* den_re, struct Int128* num_im, struct Int128* den_im) {
    int sign_re = 1;

    if (num_re->high < 0) { sign_re = -1, sign128(num_re); }

    while (num_re->high || den_re->high || num_re->low >= 0x8fffffffffffffff || den_re->low >= 0x8fffffffffffffff)
    {
        shiftright128(num_re); shiftright128(den_re);
    }

    int sign_im = 1;

    if (num_im->high < 0) { sign_im = -1, sign128(num_im); }

    while (num_im->high || den_im->high || num_im->low >= 0x8fffffffffffffff || den_im->low >= 0x8fffffffffffffff)
    {
        shiftright128(num_im); shiftright128(den_im);
    }

    struct NUMBER ret = { num_re->low * sign_re, ret.re.denominator = den_re->low, ret.im.numerator = num_im->low * sign_im, ret.im.denominator = den_im->low };
    return ret;
}


void reduce_NUMBER(struct NUMBER* N) {

    reduce(&(N->re));
    reduce(&(N->im));
}

void reduce(struct SCALAR* S) {
    if (S->denominator == 0) { S->denominator = 1; S->numerator = 0; return; }
    char sign = 0;

    if ((double)S->denominator / S->numerator < 0) sign = 1;

    if (S->numerator < 0) S->numerator = -S->numerator;
    if (S->denominator < 0) S->denominator = -S->denominator;

    long long d = gcd(S->numerator, S->denominator);

    S->denominator /= d;
    S->numerator /= d;
    if (sign) S->numerator *= -1;
}

struct NUMBER add(struct NUMBER N1, struct NUMBER N2) {

    reduce_NUMBER(&N1);
    reduce_NUMBER(&N2);

    long long gcd_re = gcd(N1.re.denominator, N2.re.denominator);

    struct Int128 den_re = mul128(N1.re.denominator / gcd_re , N2.re.denominator);
    struct Int128 num_re = add128(mul128(N1.re.numerator, N2.re.denominator / gcd_re ), mul128(N2.re.numerator, N1.re.denominator / gcd_re));
   
    long long gcd_im = gcd(N1.im.denominator, N2.im.denominator);

    struct Int128 den_im = mul128(N1.im.denominator / gcd_im, N2.im.denominator);
    struct Int128 num_im = add128(mul128(N1.im.numerator, N2.im.denominator / gcd_im ), mul128(N2.im.numerator, N1.im.denominator / gcd_im));
    
    struct NUMBER ret = combine(&num_re, &den_re, &num_im, &den_im);

    reduce_NUMBER(&ret);

    return ret;
}

struct NUMBER multiply(struct NUMBER N1, struct NUMBER N2) {
    reduce_NUMBER(&N1);
    reduce_NUMBER(&N2);

    struct Int128 re1_num = mul128(N1.re.numerator , N2.re.numerator);
    struct Int128 re1_den = mul128(N1.re.denominator , N2.re.denominator);
    struct Int128 re2_num = mul128(-N1.im.numerator , N2.im.numerator);
    struct Int128 re2_den = mul128(N1.im.denominator , N2.im.denominator);

    struct NUMBER re = add(combine(&re1_num, &re1_den, &int128_0, &int128_1), combine(&re2_num, &re2_den, &int128_0, &int128_1));

    struct Int128 im1_num = mul128(N1.re.numerator, N2.im.numerator);
    struct Int128 im1_den = mul128(N1.re.denominator, N2.im.denominator);
    struct Int128 im2_num = mul128(N1.im.numerator, N2.re.numerator);
    struct Int128 im2_den = mul128(N1.im.denominator, N2.re.denominator);

    struct NUMBER im = add(combine(&int128_0, &int128_1, & im1_num, &im1_den), combine(&int128_0, &int128_1, &im2_num, &im2_den));

    struct NUMBER ret = { re.re.numerator, re.re.denominator, im.im.numerator, im.im.denominator };

    reduce_NUMBER(&ret);

    return ret;
}

struct NUMBER divide(struct NUMBER N1, struct NUMBER N2) {
    reduce_NUMBER(&N1);
    reduce_NUMBER(&N2);

    N2.im.numerator *= -1;


    struct NUMBER num = multiply(N1, N2);

    struct Int128 res_num = mul128(N2.re.numerator , N2.re.numerator);
    struct Int128 res_den = mul128(N2.re.denominator , N2.re.denominator);
    struct Int128 ims_num = mul128(N2.im.numerator , N2.im.numerator);
    struct Int128 ims_den = mul128(N2.im.denominator , N2.im.denominator);

    struct NUMBER den = add(combine(&res_num, &res_den, &int128_0, &int128_1), combine(&ims_num, &ims_den, &int128_0, &int128_1));
    long long temp = den.re.numerator;
    den.re.numerator = den.re.denominator;
    den.re.denominator = temp;
    
    struct NUMBER ret = multiply(num, den);

    reduce_NUMBER(&ret);

    return ret;
}

struct NUMBER magnitude(struct NUMBER x) {
    struct NUMBER ret = { 0, 1, 0, 1 };
    return ret;
}

struct NUMBER ln(struct NUMBER x) {
    reduce_NUMBER(&x);
    struct NUMBER ret = { 0, 1, 0, 1 };
    if (x.im.numerator == 0) { double d = log( (double) x.re.numerator/x.re.denominator);
    }
    return ret;
}
struct NUMBER logarithm(struct NUMBER x, struct NUMBER base) {
    reduce_NUMBER(&x);
    reduce_NUMBER(&base);
    struct NUMBER ret = divide(ln(x), ln(base));
    return ret;
}

struct NUMBER power(struct NUMBER base, struct NUMBER exponent) {
    reduce_NUMBER(&base);
    reduce_NUMBER(&exponent);

    struct NUMBER ret = {1, 1, 0, 1};

    if (exponent.re.numerator == 0 && exponent.im.numerator == 0) {}
    else if (exponent.re.denominator == 1 && exponent.re.numerator > 0) {
        struct NUMBER re = { 1, 1, 0, 1 };
        for (int i = 0; i < exponent.re.numerator; i++)  re = multiply(re, base);

    }

    reduce_NUMBER(&ret);

    return ret;
}

void print_number(struct NUMBER* N) {
    if (N->re.numerator) {
        if (N->re.denominator != 1) printf("%lld/%lld", N->re.numerator, N->re.denominator);
        else printf("%lld", N->re.numerator);
    }
    if (N->re.numerator && N->im.numerator) printf(" + ");
    if (N->im.numerator) {
        if (N->im.denominator != 1) printf("%lld/%lld", N->im.numerator, N->im.denominator);
        else printf("%lld", N->im.numerator);
        printf(" i");
    }

    if (!N->re.numerator && !N->im.numerator) printf("0");


}

void print_number_dec(struct NUMBER* N) {
    if (N->re.numerator) {
        double re = (double)N->re.numerator / N->re.denominator;
        printf("%.17f\n", re);
    }
    if (N->re.numerator && N->im.numerator) printf(" + ");
    if (N->im.numerator) {
        double im = (double)N->im.numerator / (double)N->im.denominator;
        printf("%.17f\n", im);
    }

    if (!N->re.numerator && !N->im.numerator) printf("0");


}