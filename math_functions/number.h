#ifndef NUMBER_H
#define NUMBER_H

#include "Headers.h"

struct NUMBER
{
    struct SCALAR re;
    struct SCALAR im;
};

//number methods
unsigned long long gcd(long long a, long long b);

//conversion

double SCALAR_to_double(struct SCALAR* x);
struct NUMBER double_to_NUMBER(double d);
struct NUMBER String_to_NUMBER(char* number, int base);

struct NUMBER combine(struct Int128* num_re, struct Int128* den_re, struct Int128* num_im, struct Int128* den_im);

void reduce_NUMBER(struct NUMBER* N);
void reduce(struct SCALAR* S);

struct NUMBER add(struct NUMBER N1, struct NUMBER N2);
struct NUMBER multiply(struct NUMBER N1, struct NUMBER N2);
struct NUMBER divide(struct NUMBER N1, struct NUMBER N2);

struct NUMBER magnitude(struct NUMBER x);
struct NUMBER ln(struct NUMBER x);
struct NUMBER logarithm(struct NUMBER x, struct NUMBER base);

struct NUMBER power(struct NUMBER base, struct NUMBER exponent);

void print_number(struct NUMBER* N);

#endif // !NUMBER_H

