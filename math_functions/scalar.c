#include "Headers.h"

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

struct SCALAR combine_to_SCALAR(struct Int128* num, struct Int128* den) {
    int sign_re = 1;

    if (num->high < 0) { sign_re = -1, sign128(num); }
    if (den->high < 0) { sign_re = -1, sign128(den); }

    while (num->high || den->high || num->low >= 0x7fffffffffffffff || den->low >= 0xfffffffffffffff)
    {
        shiftright128(num); shiftright128(den);
    }

    struct SCALAR ret = { num->low * sign_re, ret.denominator = den->low };
    return ret;
}

struct SCALAR round_SCALAR(struct SCALAR* S, int range) {
    struct SCALAR sols[1001];
    struct SCALAR ret;
    for (int i = -range; i < range + 1; i++) { sols[i + range].denominator = S->denominator;  sols[i + range].numerator = S->numerator + i; reduce(&sols[i + range]); }
    ret = sols[0];
    for (int i = 1; i <= 2 * range; i++) { if (ret.denominator > sols[i].denominator) { ret = sols[i]; } }
    return ret;
};

struct SCALAR mul_SCALAR(struct SCALAR S1, struct SCALAR S2) {
    reduce(&S1);
    reduce(&S2);
    long long tempnum = S1.numerator;
    S1.numerator = S2.numerator;
    S2.numerator = tempnum;
    reduce(&S1);
    reduce(&S2);
    struct Int128 num = mul128(S1.numerator, S2.numerator);
    struct Int128 den = mul128(S1.denominator, S2.denominator);
    struct SCALAR ret = combine_to_SCALAR(&num, &den);
    reduce(&ret);
    return ret;

}

struct SCALAR div_SCALAR(struct SCALAR S1, struct SCALAR S2) {
    reduce(&S1);
    reduce(&S2);
    long long tempnum = S1.numerator;
    S1.numerator = S2.denominator;
    S2.denominator = tempnum;
    reduce(&S1);
    reduce(&S2);
    struct Int128 num = mul128(S1.numerator, S2.denominator);
    struct Int128 den = mul128(S1.denominator, S2.numerator);
    struct SCALAR ret = combine_to_SCALAR(&num, &den);
    reduce(&ret);
    return ret;

}

struct SCALAR add_SCALAR(struct SCALAR S1, struct SCALAR S2) {
    reduce(&S1);
    reduce(&S2);

    long long gcd_ = gcd(S1.denominator, S2.denominator);

    struct Int128 den = mul128(S1.denominator / gcd_, S2.denominator);
    struct Int128 num = add128(mul128(S1.numerator, S2.denominator / gcd_), mul128(S2.numerator, S1.denominator / gcd_));

    struct SCALAR ret = combine_to_SCALAR(&num, &den);
    return ret;
}

struct SCALAR pow_SCALAR(struct SCALAR S1, struct SCALAR S2) {
    reduce(&S1);
    reduce(&S2);
    struct SCALAR ret = double_to_SCALAR(pow(SCALAR_to_double(&S1), SCALAR_to_double(&S2)));
    ret = round_SCALAR(&ret, 20+2*log(ret.numerator / ret.denominator) );
    return ret;
    
}
struct SCALAR log_SCALAR(struct SCALAR S1, struct SCALAR S2) {
    reduce(&S1);
    reduce(&S2);
    return double_to_SCALAR(log(SCALAR_to_double(&S1))/ log(SCALAR_to_double(&S2)));
}
    
struct SCALAR ln_SCALAR(struct SCALAR S1) {
    return double_to_SCALAR(log(SCALAR_to_double(&S1)));
}
struct SCALAR sin_SCALAR(struct SCALAR S1) {}
struct SCALAR cos_SCALAR(struct SCALAR S1) {}
struct SCALAR tan_SCALAR(struct SCALAR S1) {}

void print_SCALAR(struct SCALAR* x) {
    printf("%lld / %lld", x->numerator, x->denominator);
}