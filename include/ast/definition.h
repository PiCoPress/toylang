#ifndef __DEFINITION_H
#define __DEFINITION_H

#include "expr.h"
#include "type.h"

enum ALLOC_TYPE {
    ALLOC_MUTABLE,
    ALLOC_CONST,
};

struct node_def_var {
    struct node_expr expr;
    char *symbol;
    enum BASE_TYPE def_type;
    enum ALLOC_TYPE is_const;
    int is_ptr;
};

#endif
