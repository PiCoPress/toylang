#include <stdlib.h>
#include <string.h>

#include "tokenizer.h"

enum CHARTYPE {
    ALPHABET_OR_UNDERBAR = 0,
    DECIMAL,
    BLANK,
    SPECIAL,
};

void init_token_list(struct st_token_list *obj)
{
    obj->size = 0;
    obj->capacity =  256;
    obj->arr = (struct token_t*)malloc(256 * sizeof(struct token_t));
}

void delete_token_list(struct st_token_list *obj)
{
    if(obj->arr != NULL)
    {
        int siz = obj->size;
        for(int i = 0; i < siz; ++ i)
        {
            if(obj->arr[i].is_dyn_alloc)
            {
                free(obj->arr[i].value.ptr);
            }
        }
        free(obj->arr);
        obj->arr = NULL;
    }
}

int push_token_list(struct st_token_list *obj, struct token_t *new_tok)
{
    int siz = obj->size, cap = obj->capacity;
    struct token_t *arr = obj->arr;

    if(siz >= cap)
    {
        cap += 256;
        arr = (struct token_t*)
                    realloc(arr, cap * sizeof(struct token_t));

        if(arr == NULL) return 1;
    }
    // copy here...?
    arr[siz] = *new_tok;

    obj->arr = arr;
    obj->capacity = cap;
    ++ obj->size;

    return 0;
}

/*  0: alphabets or underbar
 *  1: decimals
 *  2: blanks
 *  3: special characters
 */
enum CHARTYPE get_char_type(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        return ALPHABET_OR_UNDERBAR;
    if(c >= '0' && c <= '9') return DECIMAL;
    if(c == ' ' || c == '\t' || c == '\n') return BLANK;
    else return SPECIAL;
}

/*  Assume that the first character is CHARTYPE 0 -> allows only 0 and 1
 *
 *  Returns word length if success, else returns negative number
 */
int collect_word(char *buffer, char **cursor_ptr)
{
    int idx = 0;
    int stop = 0;
    while(1)
    {
        if(idx > 255) return -1;
        switch(get_char_type(**cursor_ptr))
        {
            case 0: case 1:
                buffer[idx] = **cursor_ptr;
            break;

            default:
                stop = 1;
                break;
        }
        if(stop == 1) break;

        ++ *cursor_ptr;
        ++ idx;
    }
    
    buffer[idx] = '\0';
    return idx;
}

inline void zeroing_unused(struct token_t *tok)
{
    tok->is_dyn_alloc = 0;
    tok->is_ptr = 0;
    tok->value.num = 0;
}

inline void identify_word_as_symbol(struct token_t *tok, char *buffer, int buf_len)
{
    tok->type = TOK_SYMBOL;
    tok->is_dyn_alloc = 1;
    tok->is_ptr = 1;
    tok->value.ptr = malloc(buf_len + 1);
    memcpy(tok->value.ptr, buffer, buf_len + 1);
}

inline void identify_word_1(struct token_t *tok, char *buffer)
{
    identify_word_as_symbol(tok, buffer, 1);
}

inline void identify_word_2(struct token_t *tok, char *buffer)
{
    if(!strncmp("if", buffer, 2))
    {
        tok->type = TOK_ST_IF;
        zeroing_unused(tok);
    }
    else // seems to be a symbol
        identify_word_as_symbol(tok, buffer, 2);
}

inline void identify_word_3(struct token_t *tok, char *buffer)
{
    if(!strncmp("for", buffer, 3))
    {
        tok->type = TOK_ST_FOR;
        zeroing_unused(tok);
    }
    else if(!strncmp("let", buffer, 3))
    {
        tok->type = TOK_DEF_VAR;
        zeroing_unused(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 3);
}

inline void identify_word_4(struct token_t *tok, char *buffer)
{
    if(!strncmp("else", buffer, 4))
    {
        tok->type = TOK_ST_ELSE;
        zeroing_unused(tok);
    }
    else if(!strncmp("func", buffer, 4))
    {
        tok->type = TOK_DEF_FUNC;
        zeroing_unused(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 4);
}

inline void identify_word_5(struct token_t *tok, char *buffer)
{
    if(!strncmp("while", buffer, 5))
    {
        tok->type = TOK_ST_WHILE;
        zeroing_unused(tok);
    }
    else if(!strncmp("break", buffer, 5))
    {
        tok->type = TOK_ST_BREAK;
        zeroing_unused(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 5);
}

inline void identify_word_6(struct token_t *tok, char *buffer)
{
    if(!strncmp("return", buffer, 6))
    {
        tok->type = TOK_ST_RET;
        zeroing_unused(tok);
    }
    else
        identify_word_as_symbol(tok, buffer, 6);
}

inline void identify_word_7(struct token_t *tok, char *buffer)
{
    identify_word_as_symbol(tok, buffer, 7);
}

inline void identify_word_8(struct token_t *tok, char *buffer)
{
    if(!strncmp("continue", buffer, 8))
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
int identify_word(struct token_t *tok, char *buffer, int buf_len)
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

// This doesn't initialize struct st_token_list obj
int tokenizer(struct st_token_list *obj, char *source)
{
    char buffer[256] = "";
    struct token_t tok;
    char *cursor = source;

    int buf_len = 0;
    int cod = 0;

    while(1)
    {
        if(*cursor == '\0') break;

        switch(get_char_type(*cursor))
        {
            case ALPHABET_OR_UNDERBAR:
            {
                buf_len = collect_word(buffer, &cursor);
                if(buf_len < 0) return -2;

                cod = identify_word(&tok, buffer, buf_len);
                if(cod < 0) return -1;

                push_token_list(obj, &tok);
                break;
            }

            case DECIMAL: return -1;
            case BLANK: ++ cursor; break;
            case SPECIAL: return -1;
        }
    }

    return 0;
}
