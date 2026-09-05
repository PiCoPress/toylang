/*  
    Processes special characters(such as non alnums)
 */

#ifndef __TOK_SPECIALS_H
#define __TOK_SPECIALS_H

#include "stringtools.h"
#include "ast/tokens.h"
#include "tokenizer.h"

extern const struct token_map TOKEN_MAPPER_SPC[256];

int is_always_single_char(char c);
int collect_special(struct string *str, char **cursor_ptr, char *const source_end);

#endif