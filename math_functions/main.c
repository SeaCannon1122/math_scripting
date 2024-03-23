#include "Headers.h"



int main() {

    struct FUNCTION_NODE* f = node();
    f->n[0] = node();
    f->n[1] = node();
    f->n[1]->n[0] = node();
    f->n[1]->n[1] = node();

    fill_node_operation(f,DIV);
    
    struct NUMBER one = { 1, 1, 0, 1 };
    struct NUMBER two = { 2, 1, 0, 1 };
    
    fill_node_number(f->n[0], one);

    fill_node_operation(f->n[1], PLUS);

    fill_node_variable(f->n[1]->n[0], var);
    fill_node_variable(f->n[1]->n[1], var);

    struct FUNCTION_NODE* y = node();
    y->n[0] = node();
    y->n[1] = node();
    fill_node_operation(y, MUL);
    fill_node_number(y->n[0], one);
    fill_node_variable(y->n[1], var);

    print_node(f);
    printf("\n\n");
    print_node(y);
    printf("\n\n");
    struct FUNCTION_NODE* sub = copy_node(f);
    sub = replace_var(sub, y, var);
    struct FUNCTION_NODE* subp = derive(sub, var);
    struct FUNCTION_NODE* subpp = derive(subp, var);

    
    simplify(sub);
    simplify(subpp);
    print_node(sub);
    printf("\n..\n");
    print_node(subp);
    printf("\n..\n");
    print_node(subpp);
    delete_node(f);
    delete_node(y);
    delete_node(sub);
    delete_node(subp);
    delete_node(subpp);
   




    struct FUNCTION_NODE* x = node();
    fill_node_operation(x, MUL);
    x->n[0] = node();
    x->n[1] = node();
    fill_node_variable(x->n[1], var);
    fill_node_number(x->n[0], one);
    simplify(x);
    print_node(x);
    delete_node(x);

    /*
    struct SCALAR x = { 4294967296 , 25 };
    struct SCALAR y = { 1 , 2};
    struct SCALAR a = pow_SCALAR(x, y);
    print_SCALAR(&a);
    */


   //for(int i = 0; i< 1000000; i++) multiply(a, b);

    return 0;
}