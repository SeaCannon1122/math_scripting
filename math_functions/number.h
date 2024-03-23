#ifndef NUMBER_H
#define NUMBER_H

#include "Headers.h"

struct NUMBER
{
    struct SCALAR re;
    struct SCALAR im;
};


//conversion
struct NUMBER combine_to_NUMBER(struct Int128* num_re, struct Int128* den_re, struct Int128* num_im, struct Int128* den_im);

void reduce_NUMBER(struct NUMBER* N);


struct NUMBER add_NUMBER(struct NUMBER N1, struct NUMBER N2);
struct NUMBER mul_NUMBER(struct NUMBER N1, struct NUMBER N2);
struct NUMBER div_NUMBER(struct NUMBER N1, struct NUMBER N2);

struct NUMBER magnitude(struct NUMBER x);
struct NUMBER ln_NUMBER(struct NUMBER x);
struct NUMBER logarithm_NUMBER(struct NUMBER x, struct NUMBER base);

struct NUMBER power_NUMBER(struct NUMBER base, struct NUMBER exponent);

void print_NUMBER(struct NUMBER* N);
void print_NUMER_dec(struct NUMBER* N);

#endif // !NUMBER_H

