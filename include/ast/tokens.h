#ifndef __TOKENS_H
#define __TOKENS_H

enum TOKENS {
    TOK_ADD,
    TOK_SUB,
    TOK_MUL,
    TOK_DIV,
};

struct token_t {
    enum TOKENS type;
    union {
        char *as_str;
        long as_long;
    } value;
};

#endif