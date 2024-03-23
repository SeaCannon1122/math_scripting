#ifndef GENERAL_H
#define GENERAL_H

#include "Headers.h"

extern struct Int128 int128_0;
extern struct Int128 int128_1;

extern struct SCALAR s0;

unsigned long long gcd(long long a, long long b);

double SCALAR_to_double(struct SCALAR* x);
struct SCALAR double_to_SCALAR(double d);
struct NUMBER double_to_NUMBER(double d);
struct NUMBER String_to_NUMBER(char* number, int base);

#endif // !GENERAL_H


