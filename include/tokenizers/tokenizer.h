#ifndef __TOKENIZER_H
#define __TOKENIZER_H

#include "ast/ast.h"
#include "ast/tokens.h"

enum CHARTYPE {
    ALPHABET_OR_UNDERSCORE = 0,
    DECIMAL,
    BLANK,
    SPECIAL,
};

struct st_token_list {
    int capacity;
    int size;
    struct token_t *arr;
};

enum CHARTYPE get_char_type(char c);

void token_clear(struct token_t *tok);

/* Should call token_list_delete after use */
void token_list_init(struct st_token_list *obj);
void token_list_delete(struct st_token_list *obj);
int token_list_push(struct st_token_list *obj, struct token_t *new_tok);

int tokenizer(struct st_token_list *obj, char *source, int source_len);

// return a char [idx + num]
int lookahead(char *cursor, char *source_end, int num);

#endif
