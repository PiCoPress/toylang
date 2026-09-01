#include <stdlib.h>
#include <string.h>

#include "tokenizers/words.h"

/*  Assume that the first character is CHARTYPE 0 -> allows only 0 and 1
 *
 *  Returns word length if success, else returns negative number
 */
int collect_word(struct string *buffer, char **cursor_ptr, char *const source_end)
{
    int stop = 0;

    reset_string(buffer);
    while(1)
    {
        if(*cursor_ptr >= source_end) break;
        switch(get_char_type(**cursor_ptr))
        {
            case ALPHABET_OR_UNDERSCORE: case DECIMAL:
                append_string(buffer, *cursor_ptr, 1);
            break;

            default:
                stop = 1;
                break;
        }
        if(stop == 1) break;

        ++ *cursor_ptr;
    }
    
    edit_char(buffer, buffer->length, '\0');
    return buffer->length;
}

inline void zeroing_unused(struct token_t *tok)
{
    tok->is_dyn_alloc = 0;
    tok->is_ptr = 0;
    tok->value.num = 0;
    tok->tag = 0;
}

inline void identify_word_as_symbol(struct token_t *tok, struct string *buffer, int buf_len)
{
    tok->type = TOK_SYMBOL;
    tok->is_dyn_alloc = 1;
    tok->is_ptr = 1;
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
        zeroing_unused(tok);
    }
    else // seems to be a symbol
        identify_word_as_symbol(tok, buffer, 2);
}

inline void identify_word_3(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("for", buffer->str, 3))
    {
        tok->type = TOK_ST_FOR;
        zeroing_unused(tok);
    }
    else if(!strncmp("let", buffer->str, 3))
    {
        tok->type = TOK_DEF_VAR;
        zeroing_unused(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 3);
}

inline void identify_word_4(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("else", buffer->str, 4))
    {
        tok->type = TOK_ST_ELSE;
        zeroing_unused(tok);
    }
    else if(!strncmp("func", buffer->str, 4))
    {
        tok->type = TOK_DEF_FUNC;
        zeroing_unused(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 4);
}

inline void identify_word_5(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("while", buffer->str, 5))
    {
        tok->type = TOK_ST_WHILE;
        zeroing_unused(tok);
    }
    else if(!strncmp("break", buffer->str, 5))
    {
        tok->type = TOK_ST_BREAK;
        zeroing_unused(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 5);
}

inline void identify_word_6(struct token_t *tok, struct string *buffer)
{
    if(!strncmp("return", buffer->str, 6))
    {
        tok->type = TOK_ST_RET;
        zeroing_unused(tok);
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
        zeroing_unused(tok);
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
