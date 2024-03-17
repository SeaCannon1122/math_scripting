#ifndef INT128_H
#define INT128_H

#include "Headers.h"

struct Int128 {
    unsigned long long low;
    signed long long high;
};


extern struct Int128 mul128(long long a, long long b);
void print128(struct Int128* x);
struct Int128 add128(struct Int128 a, struct Int128 b);
void sign128(struct Int128* x);
void shiftright128(struct Int128* x);

#endif // !INT128_H
