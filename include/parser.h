#ifndef __PARSER_H
#define __PARSER_H

#include "tokenizers/tokenizer.h"
#include "ast/ast.h"

int parser(struct st_token_list *tok_list);

#endif