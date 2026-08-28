#ifndef __AST_H
#define __AST_H

#include "statement.h"

struct AST {
    int length;
    struct node_statement *statement[];
};

#endif