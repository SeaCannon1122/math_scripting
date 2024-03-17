#include "Headers.h"



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

    //struct NUMBER a = { 11, 3, 2, -12 };
    //struct NUMBER b = { 7, 5, -4, 394 };
    //char number[] = "-110.1\0";
    //struct NUMBER c = String_to_NUMBER(number, 2);
    double d = 187.6942;
    struct NUMBER c = double_to_NUMBER(d);


   //for(int i = 0; i< 1000000; i++) multiply(a, b);

    print_number(&c);

    return 0;
}