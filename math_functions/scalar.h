#ifndef SCALAR_H
#define SCALAR_H

#include "Headers.h"

struct SCALAR {
    long long numerator;
    long long denominator;
};

void reduce(struct SCALAR* S);
struct SCALAR combine_to_SCALAR(struct Int128* num, struct Int128* den);
struct SCALAR round_SCALAR(struct SCALAR* S, int range);
struct SCALAR mul_SCALAR(struct SCALAR S1, struct SCALAR S2);
struct SCALAR div_SCALAR(struct SCALAR S1, struct SCALAR S2);
struct SCALAR add_SCALAR(struct SCALAR S1, struct SCALAR S2);

struct SCALAR pow_SCALAR(struct SCALAR S1, struct SCALAR S2);
struct SCALAR log_SCALAR(struct SCALAR S1, struct SCALAR S2);
struct SCALAR ln_SCALAR(struct SCALAR S1);
struct SCALAR sin_SCALAR(struct SCALAR S1);
struct SCALAR cos_SCALAR(struct SCALAR S1);
struct SCALAR tan_SCALAR(struct SCALAR S1);



#endif // !SCALAR_H
