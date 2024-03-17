#ifndef SCALAR_H
#define SCALAR_H

#include "Headers.h"

struct SCALAR {
    long long numerator;
    long long denominator;
};

struct SCALAR combine123(struct Int128* num, struct Int128* den);
struct SCALAR round_SCALAR(struct SCALAR* S, int range);


#endif // !SCALAR_H
