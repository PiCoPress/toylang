#ifndef __EXPR_H
#define __EXPR_H

#include "tokens.h"
#include "literal.h"

enum EXPR_OPERATOR_TYPE {
    OP_NONE,

    OP_NOT,
    OP_AND,
    OP_OR,

    OP_EQUAL,
    OP_NOT_EQUAL,
    OP_GREATER_THAN,
    OP_GREATER_EQUAL,
    OP_LESS_THAN,
    OP_LESS_EQUAL,

    OP_ADD,
    OP_SUB,
    OP_MUL,
    OP_DIV,
    OP_MOD,

    OP_DEC_PRE,
    OP_DEC_POST,
    OP_INC_PRE,
    OP_INC_POST,

    OP_BIT_NOT,
    OP_BIT_OR,
    OP_BIT_AND,
    OP_BIT_XOR,
    OP_SHFT_L,
    OP_SHFT_R,

    OP_ADDR,
    OP_DEREF,
};

enum OPERATOR_KIND {
    KD_LITERAL,
    KD_UNARY,
    KD_BINARY,
    KD_FN_CALL,
};

struct node_expr_unary {
    struct node_expr *mono;
};

struct node_expr_binary {
    struct node_expr *left;
    struct node_expr *right;
};

struct node_func_call {
    long symbol;
    int argc;
    struct node_expr *args;
};

struct node_expr {
    enum EXPR_OPERATOR_TYPE opr_type;
    enum OPERATOR_KIND kind;
    union {
        struct node_literal self;
        struct node_expr_unary unary;
        struct node_expr_binary binary;
        struct node_func_call func_call;
    } body;
};

#endif