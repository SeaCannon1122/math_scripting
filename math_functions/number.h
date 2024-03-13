#ifndef NUMBER_H
#define NUMBER_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct NUMBER
{
    long long numerator_re;
    long long denominator_re;

    long long numerator_im;
    long long denominator_im;
};

unsigned long long gcd(long long a, long long b);

void reduce(struct NUMBER* N);

struct NUMBER add(struct NUMBER N1, struct NUMBER N2);
struct NUMBER subtract(struct NUMBER N1, struct NUMBER N2);
struct NUMBER multiply(struct NUMBER N1, struct NUMBER N2);
struct NUMBER divide(struct NUMBER N1, struct NUMBER N2);

void print_number(struct NUMBER* N);

#endif // !NUMBER_H

