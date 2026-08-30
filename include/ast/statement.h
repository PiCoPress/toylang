#ifndef __STATEMENT_H
#define __STATEMENT_H

#include "expr.h"
#include "ast.h"
#include "definition.h"

enum STATEMENT_TYPE {
    ST_EXPR,
    ST_IF,
    ST_WHILE,
    ST_FOR,
    ST_RETURN,
};

struct node_statement_if {
    struct node_expr condition;
    struct AST *block_ok;
    struct AST *block_else;
};

struct node_statement_while {
    struct node_expr condition;
    struct AST *block;
};

struct node_statement_for {
    struct node_def_var var;
    struct node_expr condition;
    struct node_expr post_run;
    struct AST *block;
};

struct node_statement_return {
    struct node_expr ret;
};

struct node_statement {
    enum STATEMENT_TYPE st_type;
    union {
        struct node_expr expr;
        struct node_statement_if st_if;
        struct node_statement_while st_while;
        struct node_statement_for st_for;
        struct node_statement_return st_return;
    } body;
};
#endif
