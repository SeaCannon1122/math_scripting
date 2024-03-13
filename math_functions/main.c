#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "number.h"
#include "function.h"

/*struct NUMBER power(struct NUMBER base, struct NUMBER exponent) {
    reduce(&base);
    reduce(&exponent);

    double based = (double) base.numerator_re / base.denominator_re;
    double exponentd = (double) exponent.numerator_re / exponent.denominator_re;

    double powd = pow(based, exponentd);

    long long two = 1;

    while(two * 2 * powd > 0 && two * 2 > 0) two*=2;

    struct NUMBER ret = {two * powd, two};

    return ret;
}*/



int main() {

    struct FUNCTION_NODE* f = node();
    f->n[0] = node();
    f->n[1] = node();

    fill_node_operation(f, DIV);

    struct NUMBER a = { 1, 1 };
    fill_node_number(f->n[0], a);

    fill_node_variable(f->n[1], var);

    print_node(f);
    printf("\n\n");
    struct FUNCTION_NODE* fprime = node();
    fprime = derive(f, var);
    simplefy(fprime);
    print_node(fprime);
    printf("\n\n");
    print_node(f);

    delete_node(f);
    delete_node(fprime);

    return 0;
}