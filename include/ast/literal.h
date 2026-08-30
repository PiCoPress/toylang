#ifndef __LITERAL_H
#define __LITERAL_H

enum LITERAL_TYPE {
    LIT_INTEGER,
    LIT_FLOAT,
    LIT_CHAR,
    LIT_STRING,

    LIT_SYMBOL,
};

struct node_literal {
    void *value;
    enum LITERAL_TYPE lit_type;
};

#endif
