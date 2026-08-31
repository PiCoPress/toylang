#include <stdlib.h>
#include <string.h>

#include "tokenizers/tokenizer.h"
#include "tokenizers/words.h"
#include "stringtools.h"

enum CHARTYPE get_char_type(char c)
{
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_')
        return ALPHABET_OR_UNDERBAR;
    if(c >= '0' && c <= '9') return DECIMAL;
    if(c == ' ' || c == '\t' || c == '\n') return BLANK;
    else return SPECIAL;
}

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

// This doesn't initialize struct st_token_list obj
int tokenizer(struct st_token_list *obj, char *source)
{
    struct string buffer;
    struct token_t tok;
    char *cursor = source;

    int buf_len = 0;

    create_string(&buffer);

    while(1)
    {
        if(*cursor == '\0') break;

        switch(get_char_type(*cursor))
        {
            case ALPHABET_OR_UNDERBAR:
            {
                buf_len = collect_word(&buffer, &cursor);
                if(buf_len <= 0)
                {
                    destroy_string(&buffer);
                    return -2;
                }

                // always buf_len > 0
                identify_word(&tok, &buffer, buf_len);

                push_token_list(obj, &tok);
                break;
            }

            case DECIMAL: goto err;
            case BLANK: ++ cursor; break;
            case SPECIAL: goto err;
        }
    }

    destroy_string(&buffer);
    return 0;

err:
    destroy_string(&buffer);
    return -1;
}
