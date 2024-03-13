#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

extern char PLUS[32];
extern char MINUS[32];
extern char MUL[32];
extern char DIV[32];
extern char var[32];

struct FUNCTION_NODE {
    char type;
    char content[32];
    struct FUNCTION_NODE* n[16];
};

//17th byte
//0 = NUMBER
//1 = Operator
//2 = internal function 
//3 = variable input
//4 = external function

struct FUNCTION_NODE* node();
void delete_node(struct FUNCTION_NODE* n);
void clear_node(struct FUNCTION_NODE* n);

void fill_node_number(struct FUNCTION_NODE* n, struct NUMBER N);
void fill_node_operation(struct FUNCTION_NODE* n, char name[32]);
void fill_node_variable(struct FUNCTION_NODE* n, char name[32]);

struct FUNCTION_NODE* copy_node(struct FUNCTION_NODE* n);
void print_node(struct FUNCTION_NODE* n);
void simplify(struct FUNCTION_NODE* n);
struct FUNCTION_NODE* derive(struct FUNCTION_NODE* n, char respectablevar[32]);

#endif // !FUNCTION_H
