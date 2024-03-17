#include "Headers.h"

struct SCALAR combine123(struct Int128* num, struct Int128* den) {
    int sign_re = 1;

    if (num->high < 0) { sign_re = -1, sign128(num); }

    while (num->high || den->high || num->low >= 0x7fffffffffffffff || den->low >= 0xfffffffffffffff)
    {
        shiftright128(num); shiftright128(den);
    }

    struct SCALAR ret = { num->low * sign_re, ret.denominator = den->low };
    return ret;
}

struct SCALAR round_SCALAR(struct SCALAR* S, int range) {
    struct SCALAR sols[21];
    struct SCALAR ret;
    for (int i = -range; i < range + 1; i++) { sols[i + range].denominator = S->denominator;  sols[i + range].numerator = S->numerator + i; reduce(&sols[i + range]); }
    ret = sols[0];
    for (int i = 1; i <= 2 * range; i++) { if (ret.denominator > sols[i].denominator) { ret = sols[i]; } }
    return ret;
};
