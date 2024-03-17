#include "Headers.h"

void print128(struct Int128* x) {
    long long low = x->low;
    long long high = x->high;
    char sign = 0;
    if (high < 0) {
        sign = '-';
        low = ~low;
        high = ~high;
        low++;

        if (!low) high++;
    }

    if (high) {
        printf("%c%llx", sign, high);
        char* ptr = (char*)&low;
        for (int i = 7; i >= 0; i--) {
            if ((ptr[i] & 0b11110000) == 0) printf("0");
            else break;
            if ((ptr[i] & 0b00001111) == 0) printf("0");
            else break;
        }
        printf("%llx", low);
    }
    else printf("%c%llx", sign, low);

}

struct Int128 add128(struct Int128 a, struct Int128 b) {
    struct Int128 res = { a.low + b.low, a.high + b.high };
    if (res.low < a.low) res.high++;
    return res;

}

void sign128(struct Int128* x) {
    x->low = ~x->low;
    x->high = ~x->high;
    x->low++;

    if (!x->low) x->high++;
}

void shiftright128(struct Int128* x) {
    x->low >>= 1;
    if (x->high & 0x1) x->low |= 0x8000000000000000;
    x->high >>= 1;
}