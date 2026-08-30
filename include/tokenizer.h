#ifndef __TOKENIZER_H
#define __TOKENIZER_H

#include "ast/ast.h"
#include "ast/tokens.h"

struct st_token_list {
    int capacity;
    int size;
    struct token_t *arr;
};

/* Should call delete_token_list after use */
void init_token_list(struct st_token_list *obj);
void delete_token_list(struct st_token_list *obj);
int push_token_list(struct st_token_list *obj, struct token_t *new_tok);

int tokenizer(struct st_token_list *obj, char *source);

#endif
