#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "number.h"
#include "function.h"




int main() {

    /*struct FUNCTION_NODE* f = node();
    f->n[0] = node();
    f->n[1] = node();
    f->n[1]->n[0] = node();
    f->n[1]->n[1] = node();

    fill_node_operation(f,DIV);

    struct NUMBER one = { 1, 1, 0, 1 };
    fill_node_number(f->n[0], one);

    fill_node_operation(f->n[1], MUL);

    fill_node_variable(f->n[1]->n[0], var);
    fill_node_variable(f->n[1]->n[1], var);

    print_node(f);
    printf("\n\n");
    struct FUNCTION_NODE* fprime = node();
    fprime = derive(f, var);
    print_node(fprime);
    printf("\n\n");
    print_node(f);

    delete_node(f);
    delete_node(fprime);
    */

    struct Int128 a = mul128(0x7ffffffffffffff0, 0x7fffffffffffffff);
    struct Int128 b = mul128(0x7fffffffffffffff, 0x7fffffffffffffff);
    struct Int128 result = add128(a, b);
    printf("%llx   %llx\n", a.low, a.high);
    print128(&a);
    printf("\n");
    print128(&b);
    printf("\n");
    print128(&result);

    return 0;
}