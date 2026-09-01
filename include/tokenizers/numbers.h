#ifndef __TOK_DECIMALS_H
#define __TOK_DECIMALS_H

#include "stringtools.h"
#include "ast/tokens.h"
#include "tokenizer.h"

int collect_decimal(struct string *str, char **cursor_ptr, char *const source_end);
int collect_number(struct token_t *tok, struct string *str, char **cursor_ptr, char *const source_end);
void generate_number(struct token_t *tok, struct string *buffer, int mode);

#endif
