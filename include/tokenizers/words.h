#ifndef __TOK_WORDS_H
#define __TOK_WORDS_H

#include "ast/tokens.h"
#include "tokenizer.h"
#include "stringtools.h"

/*  Assume that the first character is CHARTYPE 0 -> allows only 0 and 1
 *
 *  Returns word length if success, else returns negative number
 */
int collect_word(struct string *str, char **cursor_ptr, char *const source_end);

void zeroing_unused(struct token_t *tok);
void identify_word_as_symbol(struct token_t *tok, struct string *buffer, int buf_len);

void identify_word_1(struct token_t *tok, struct string *buffer);
void identify_word_2(struct token_t *tok, struct string *buffer);
void identify_word_3(struct token_t *tok, struct string *buffer);
void identify_word_4(struct token_t *tok, struct string *buffer);
void identify_word_5(struct token_t *tok, struct string *buffer);
void identify_word_6(struct token_t *tok, struct string *buffer);
void identify_word_7(struct token_t *tok, struct string *buffer);
void identify_word_8(struct token_t *tok, struct string *buffer);

/*
    Look up the word length if there are keywords which are same size,
    to reduce the comparison
 */
int identify_word(struct token_t *tok, struct string *buffer, int buf_len);

#endif
