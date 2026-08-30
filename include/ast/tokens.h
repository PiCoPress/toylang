#ifndef __TOKENS_H
#define __TOKENS_H

enum TOKENS {
    TOK_LITERAL,
    TOK_SYMBOL,
    TOK_ASSIGN,
    TOK_SEMI,

    TOK_OPR_ADD,
    TOK_OPR_SUB,
    TOK_OPR_MUL,
    TOK_OPR_DIV,
    TOK_OPR_MOD,
    TOK_OPR_INC,
    TOK_OPR_DEC,
    TOK_OPR_SHL,
    TOK_OPR_SHR,
    TOK_OPR_AND,
    TOK_OPR_OR,
    TOK_OPR_XOR,
    TOK_OPR_NOT,
    TOK_OPR_GT,
    TOK_OPR_GE,
    TOK_OPR_LT,
    TOK_OPR_LE,
    TOK_OPR_ADDR,
    TOK_OPR_DEREF,
    TOK_LOGIC_AND,
    TOK_LOGIC_OR,
    TOK_LOGIC_NOT,
    TOK_LOGIC_EQ,
    TOK_LOGIC_NE,

    TOK_ST_BLK_BEGIN,
    TOK_ST_BLK_END,
    TOK_ST_FOR,
    TOK_ST_WHILE,
    TOK_ST_IF,
    TOK_ST_ELSE,
    TOK_ST_CONT,
    TOK_ST_BREAK,
    TOK_ST_RET,

    TOK_PAR_OPEN, // Parentheses
    TOK_PAR_CLOSE,

    TOK_DEF_VAR,
    TOK_DEF_FUNC,

    TOK_DUMMY_LAST
};

extern const char *STRING_TOKENS[TOK_DUMMY_LAST];

/*
    literal
 */
struct token_t {
    enum TOKENS type;
    union {
        void *ptr;
        long num;
    } value;
    short is_dyn_alloc;
    short is_ptr;
};

#endif
