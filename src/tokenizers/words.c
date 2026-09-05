#include <stdlib.h>
#include <string.h>

#include "tokenizers/words.h"

/*  Assume that the first character is CHARTYPE 0 -> allows only 0 and 1
 *
 *  Returns word length if success, else returns negative number
 */
int collect_word(struct string *buffer, char **cursor_ptr, char *const source_end)
{
    char *cursor = *cursor_ptr;
    int len = 0;
    int stop = 0;

    reset_string(buffer);
    while(1)
    {
        if(cursor >= source_end) break;
        switch(get_char_type(*cursor))
        {
            case ALPHABET_OR_UNDERSCORE: case DECIMAL:
                ++ cursor;
                break;

            default:
                stop = 1;
                break;
        }
        if(stop == 1) break;
    }

    len = cursor - *cursor_ptr;

    append_string(buffer, *cursor_ptr, len);
    append_string(buffer, "", 1);

    *cursor_ptr = cursor;
    return buffer->length - 1;
}

inline void identify_word_as_symbol(struct token_t *tok, struct string *buffer, int buf_len)
{
    tok->type = TOK_SYMBOL;
    tok->is_dyn_alloc = 1;
    tok->is_ptr = 1;
    tok->tag = 0;
    tok->value.ptr = malloc(buf_len + 1);
    memcpy(tok->value.ptr, buffer->str, buf_len + 1);
}

inline void identify_word_1(struct token_t *tok, struct string *buffer)
{
    identify_word_as_symbol(tok, buffer, 1);
}

inline void identify_word_2(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("if", buffer->str, 2))
    {
        tok->type = TOK_ST_IF;
        token_clear(tok);
    }
    else // seems to be a symbol
        identify_word_as_symbol(tok, buffer, 2);
}

inline void identify_word_3(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("for", buffer->str, 3))
    {
        tok->type = TOK_ST_FOR;
        token_clear(tok);
    }
    else if(!strncmp("let", buffer->str, 3))
    {
        tok->type = TOK_DEF_VAR;
        token_clear(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 3);
}

inline void identify_word_4(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("else", buffer->str, 4))
    {
        tok->type = TOK_ST_ELSE;
        token_clear(tok);
    }
    else if(!strncmp("func", buffer->str, 4))
    {
        tok->type = TOK_DEF_FUNC;
        token_clear(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 4);
}

inline void identify_word_5(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("while", buffer->str, 5))
    {
        tok->type = TOK_ST_WHILE;
        token_clear(tok);
    }
    else if(!strncmp("break", buffer->str, 5))
    {
        tok->type = TOK_ST_BREAK;
        token_clear(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 5);
}

inline void identify_word_6(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("return", buffer->str, 6))
    {
        tok->type = TOK_ST_RET;
        token_clear(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 6);
}

inline void identify_word_7(struct token_t *tok, struct string *buffer)
{
    identify_word_as_symbol(tok, buffer, 7);
}

inline void identify_word_8(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("continue", buffer->str, 8))
    {
        tok->type = TOK_ST_CONT;
        token_clear(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 8);
}

/*
    Look up the word length if there are keywords which are same size,
    to reduce the comparison
 */
int identify_word(struct token_t *tok, struct string *buffer, int buf_len)
{
    switch(buf_len)
    {
        case 0: return -1;
        case 1: // nothing
            identify_word_1(tok, buffer);
            break;

        case 2: // 'if', other else are symbols
            identify_word_2(tok, buffer);
            break;

        case 3: // for, let
            identify_word_3(tok, buffer);
            break;

        case 4: // else, func
            identify_word_4(tok, buffer);
            break;

        case 5: // while, break
            identify_word_5(tok, buffer);
            break;

        case 6: // return
            identify_word_6(tok, buffer);
            break;

        case 7: // nothing
            identify_word_7(tok, buffer);
            break;

        case 8: // continue
            identify_word_8(tok, buffer);
            break;

        default:
            identify_word_as_symbol(tok, buffer, buf_len);
            break;
    }

    return 0;
}
