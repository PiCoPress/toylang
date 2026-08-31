#ifndef __FUNCTION_H
#define __FUNCTION_H

#include "ast.h"
#include "expr.h"
#include "type.h"

struct node_argument {
    enum BASE_TYPE type;
    long arg_symbol;
    int is_ptr;
};

struct node_function {
    enum BASE_TYPE ret_type;
    int ret_is_ptr;
    char *func_symbol;
    struct AST *body; // Allow declare only

    int argc;
    struct node_argument args[];
};

#endif
