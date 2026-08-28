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
    if((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_') return 0;
    if(c >= '0' && c <= '9') return 1;
    if(c == ' ' || c == '\t' || c == '\n') return 2;
    else return 3;
}

/*  Assume that the first character is CHARTYPE 0 -> allows only 0 and 1
 *
 *  Returns 0 if success, else returns negative number
 */
int collect_word(char *buffer, char **cursor_ptr)
{
    int idx = 0;
    while(1)
    {
        if(idx > 255) return -1;
        switch(get_char_type(**cursor_ptr))
        {
            case 0: case 1:
                buffer[idx] = **cursor_ptr;
            break;

            default: return 0;
        }
        ++ *cursor_ptr;
        ++ idx;
    }
    return 0;
}

// This doesn't initialize struct st_token_list obj
int tokenizer(struct st_token_list *obj, char *source)
{
    char buffer[256] = "";
    struct token_t tok;
    char *cursor = source;

    while(1)
    {
        if(*cursor == '\0') break;

        switch(get_char_type(*cursor))
        {
            case ALPHABET_OR_UNDERBAR: collect_word(buffer, &cursor); break;
            case DECIMAL: break;
            case BLANK: break;
            case SPECIAL: break;
        }
    }

    return 0;
}