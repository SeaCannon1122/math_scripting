#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "number.h"
#include "function.h"

char PLUS[32] = { '+', 0 };
char MINUS[32] = { '-', 0 };
char MUL[32] = { '*', 0 };
char DIV[32] = { '/', 0 };
char var[32] = { 'x', 0 };

struct FUNCTION_NODE* node() {
    struct FUNCTION_NODE* n = (struct FUNCTION_NODE*)malloc(sizeof(struct FUNCTION_NODE));
    for (int i = 0; i < 16; i++) n->n[i] = NULL;
    for (int i = 0; i < 32; i++) n->content[i] = 0;
    n->type = 0;
    return n;
}

void fill_node_number(struct FUNCTION_NODE* n, struct NUMBER N) {
    n->type = 0;
    *((struct NUMBER*)(&(n->content))) = N;
}

void fill_node_operation(struct FUNCTION_NODE* n, char name[32]) {
    n->type = 1;
    for (int i = 0; i < 32; i++) n->content[i] = name[i];
}

void fill_node_variable(struct FUNCTION_NODE* n, char name[32]) {
    n->type = 3;
    for (int i = 0; i < 32; i++) n->content[i] = name[i];
}

struct FUNCTION_NODE* copy_node(struct FUNCTION_NODE* n) {
    struct FUNCTION_NODE* new = node();
    new->type = n->type;
    for (int i = 0; i < 32; i++) new->content[i] = n->content[i];
    for (int i = 0; i < 16; i++) {
        if (n->n[i] != NULL) new->n[i] = copy_node(n->n[i]);
        else new->n[i] = NULL;
    }
    return new;
}

void print_node(struct FUNCTION_NODE* n) {
    if (n->type == 1) {
        printf("( ");
        print_node(n->n[0]);
        printf(" ");
        for (int i = 0; i < 32; i++) printf("%c", n->content[i]);
        printf(" ");
        print_node(n->n[1]);
        printf(" )");
    }

    if (n->type == 0) print_number((struct NUMBER*)n->content);
    else if (n->type == 3) { for (int i = 0; i < 32; i++) printf("%c", n->content[i]); }

}

void delete_node(struct FUNCTION_NODE* n) {
    for (int i = 0; i < 16; i++) { if (n->n[i] != NULL) delete_node(n->n[i]); }
    free(n);
}

void clear_node(struct FUNCTION_NODE* n) {
    for (int i = 0; i < 16; i++) { if (n->n[i] != NULL) { delete_node(n->n[i]); n->n[i] = NULL; } }
}

void simplify(struct FUNCTION_NODE* n) {
    if (!n->type || n->type == 4) return;
    for (int i = 0; i < 15; i++) { if (n->n[i] != NULL) simplify(n->n[i]); }
    if (n->type == 1) {
        if (n->content[0] == '+') {

            if (n->n[0]->type == 0 && ((struct NUMBER*)n->n[0]->content)->numerator_re == 0 && ((struct NUMBER*)n->n[0]->content)->numerator_im == 0) {
                struct FUNCTION_NODE* temp = copy_node(n->n[1]);
                clear_node(n);
                *n = *temp;
            }
            else if (n->n[1]->type == 0 && ((struct NUMBER*)n->n[1]->content)->numerator_re == 0 && ((struct NUMBER*)n->n[1]->content)->numerator_im == 0) {
                struct FUNCTION_NODE* temp = copy_node(n->n[0]);
                clear_node(n);
                *n = *temp;
            }

            else if (!n->n[0]->type && !n->n[1]->type) {
                struct NUMBER sum = add(*((struct NUMBER*)n->n[0]->content), *((struct NUMBER*)n->n[1]->content));
                clear_node(n);
                fill_node_number(n, sum);
            }
        }

        else if (n->content[0] == '-') {
            if (n->n[1]->type == 0 && ((struct NUMBER*)n->n[1]->content)->numerator_re == 0 && ((struct NUMBER*)n->n[1]->content)->numerator_im == 0) {
                struct FUNCTION_NODE* temp = copy_node(n->n[0]);
                clear_node(n);
                *n = *temp;
            }

            else if (n->n[1]->type == 0 && ((struct NUMBER*)n->n[1]->content)->numerator_re == 0 && ((struct NUMBER*)n->n[1]->content)->numerator_im == 0) {
                struct FUNCTION_NODE* temp = copy_node(n->n[0]);
                clear_node(n);
                *n = *temp;
            }

            else if (!n->n[0]->type && !n->n[1]->type) {
                struct NUMBER dif = subtract(*((struct NUMBER*)n->n[0]->content), *((struct NUMBER*)n->n[1]->content));
                clear_node(n);
                fill_node_number(n, dif);
            }
        }

        else if (n->content[0] == '*') {

            if ((n->n[0]->type == 0 && ((struct NUMBER*)n->n[0]->content)->numerator_re == 0 && ((struct NUMBER*)n->n[0]->content)->numerator_im == 0) ||
                (n->n[1]->type == 0 && ((struct NUMBER*)n->n[1]->content)->numerator_re == 0 && ((struct NUMBER*)n->n[1]->content)->numerator_im == 0)) {

                clear_node(n);
                struct NUMBER N = { 0, 1, 0, 1 };
                fill_node_number(n, N);
            }

            else if (!n->n[0]->type && !n->n[1]->type) {
                struct NUMBER mul = multiply(*((struct NUMBER*)n->n[0]->content), *((struct NUMBER*)n->n[1]->content));
                clear_node(n);
                fill_node_number(n, mul);
            }
        }
    }
}

struct FUNCTION_NODE* derive(struct FUNCTION_NODE* n, char respectablevar[32]) {
    struct FUNCTION_NODE* new = node();
    if (!n->type) {
        struct NUMBER N = { 0 , 1 };
        fill_node_number(new, N);
    }

    if (n->type == 3) {
        int same = 1;
        for (int i = 0; i < 32; i++) { if (n->content[i] != respectablevar[i]) same = 0; }
        if (same) {
            struct NUMBER N1 = { 1, 1 };
            fill_node_number(new, N1);

        }
        else {
            struct NUMBER N0 = { 0, 1 };
            fill_node_number(new, N0);
        }
    }

    else if (n->type == 1) {
        if (n->content[0] == '+') {
            fill_node_operation(new, PLUS);
            new->n[0] = derive(n->n[0], respectablevar);
            new->n[1] = derive(n->n[1], respectablevar);
        }

        if (n->content[0] == '-') {
            fill_node_operation(new, MINUS);
            new->n[0] = derive(n->n[0], respectablevar);
            new->n[1] = derive(n->n[1], respectablevar);
        }

        if (n->content[0] == '*') {
            fill_node_operation(new, PLUS);

            new->n[0] = node();
            fill_node_operation(new->n[0], MUL);
            new->n[0]->n[0] = derive(n->n[0], respectablevar);
            new->n[0]->n[1] = copy_node(n->n[1]);

            new->n[1] = node();
            fill_node_operation(new->n[1], MUL);
            new->n[1]->n[0] = copy_node(n->n[0]);
            new->n[1]->n[1] = derive(n->n[1], respectablevar);
        }


        if (n->content[0] == '/') {
            fill_node_operation(new, DIV);
            new->n[0] = node();
            fill_node_operation(new->n[0], MINUS);

            new->n[0]->n[0] = node();
            fill_node_operation(new->n[0]->n[0], MUL);
            new->n[0]->n[0]->n[0] = derive(n->n[0], respectablevar);
            new->n[0]->n[0]->n[1] = copy_node(n->n[1]);

            new->n[0]->n[1] = node();
            fill_node_operation(new->n[0]->n[1], MUL);
            new->n[0]->n[1]->n[0] = copy_node(n->n[0]);
            new->n[0]->n[1]->n[1] = derive(n->n[1], respectablevar);

            new->n[1] = node();
            fill_node_operation(new->n[1], MUL);
            new->n[1]->n[0] = copy_node(n->n[1]);
            new->n[1]->n[1] = copy_node(n->n[1]);

        }

    }
    simplify(new);
    return new;
}
