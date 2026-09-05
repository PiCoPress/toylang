#include <stdlib.h>
#include <string.h>

#include "tokenizers/tokenizer.h"
#include "tokenizers/words.h"
#include "tokenizers/numbers.h"
#include "tokenizers/specials.h"

#include "stringtools.h"

enum CHARTYPE get_char_type(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        return ALPHABET_OR_UNDERSCORE;
    if(c >= '0' && c <= '9') return DECIMAL;
    if(c == ' ' || c == '\t' || c == '\n') return BLANK;
    else return SPECIAL;
}

void token_clear(struct token_t *tok)
{
    tok->is_dyn_alloc = 0;
    tok->is_ptr = 0;
    tok->value.num = 0;
    tok->tag = 0;
}

void token_list_init(struct st_token_list *obj)
{
    obj->size = 0;
    obj->capacity =  256;
    obj->arr = (struct token_t*)malloc(256 * sizeof(struct token_t));
}

void token_list_delete(struct st_token_list *obj)
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

int token_list_push(struct st_token_list *obj, struct token_t *new_tok)
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

// This doesn't initialize struct st_token_list obj
int tokenizer(struct st_token_list *obj, char *source, int source_len)
{
    struct string buffer;
    struct token_t tok = {0, };
    char *const source_end = source + source_len;
    char *cursor = source;

    int buf_len = 0;
    int err_code = 0;

    create_string(&buffer);

    while(1)
    {
        // Would be EOF
        if(cursor >= source_end) break;

        switch(get_char_type(*cursor))
        {
            case ALPHABET_OR_UNDERSCORE:
            {
                buf_len = collect_word(&buffer, &cursor, source_end);
                if(buf_len <= 0)
                {
                    err_code = -2;
                    goto err;
                }

                // always buf_len > 0
                identify_word(&tok, &buffer, buf_len);

                token_list_push(obj, &tok);
                break;
            }

            case DECIMAL:
            {
                int mode = collect_number(&buffer, &cursor, source_end);

                if(mode < 0)
                {
                    err_code = mode;
                    goto err;
                }

                generate_number(&tok, &buffer, mode);
                token_list_push(obj, &tok);
                break;
            }

            case BLANK: ++ cursor; break;

            case SPECIAL:
            {
                int test = collect_special(&buffer, &cursor, source_end);
                if(test < 0)
                {
                    err_code = test;
                    goto err;
                }

                token_clear(&tok);

                tok.type = test;

                token_list_push(obj, &tok);
                break;
            }
        }
    }

    destroy_string(&buffer);
    return 0;

err:
    destroy_string(&buffer);
    return err_code;
}

int lookahead(char *cursor, char *source_end, int num)
{
    // Guard OOB
    if(cursor + num >= source_end) return 256;
    return cursor[num];
}
