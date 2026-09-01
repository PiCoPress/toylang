#include <stdlib.h>
#include <string.h>

#include "tokenizers/numbers.h"

/*  Do not set str->length directly, because it's a sub-function.

    Will return count of collected decimals.
 */
int collect_decimal(struct string *str, char **cursor_ptr, char *const source_end)
{
    int idx = 0;
    char c;
    while(1)
    {
        if(*cursor_ptr >= source_end) break;
        c = **cursor_ptr;

        if(c >= '0' && c <= '9')
            append_string(str, *cursor_ptr, 1); // safer than edit_char
        else break;

        ++ *cursor_ptr;
        ++ idx;
    }
    return idx;
}

// I am writing spaghetti code...
int collect_number(struct token_t *tok, struct string *str, char **cursor_ptr,
    char *const source_end)
{
    // mode 0: int      mode 1: non-int
    int number_mode = 0, should_break = 0;
    char prev_char = 0, aa_cursor = **cursor_ptr;
    // aa_cursor: 'a'sterisk 'a'sterisk cursor_ptr

    reset_string(str);
    while(1)
    {
        if(*cursor_ptr >= source_end) break;
        aa_cursor = **cursor_ptr;

        switch(get_char_type(aa_cursor))
        {
            case DECIMAL:
                collect_decimal(str, cursor_ptr, source_end);
                break;

            case ALPHABET_OR_UNDERSCORE:
            {
                // Alphabets or underscores in the decimal context?
                // I will allow underscores, like Python (1_000).
                // But not allow continuous underscores.
                if(aa_cursor == '_')
                {
                    // It's better to use enum based error, but not for now?
                    if(prev_char == '_') return -2;
                    // Ignore a single underscore
                }
                else // alphabets here
                {
                    // e.g 0x, 0o 0b. so prev_char must be '0'
                    if(prev_char != '0') return -3;
                    // TODO
                    return -5;
                }
                break;
            }

            case SPECIAL: // Accepts only a dot
            {
                if(aa_cursor == '.')
                {
                    // Like a ".."
                    // So I should get the cursor back one step.
                    if(prev_char == '.')
                    {
                        -- *cursor_ptr;
                        -- str->length;
                        return 0;
                    }

                    // Like a "1.2.3"
                    if(number_mode == 1) return -4;

                    number_mode = 1;
                    ++ *cursor_ptr;

                    append_string(str, ".", 1);
                    collect_decimal(str, cursor_ptr, source_end);
                } else should_break = 1;
                break;
            }

            case BLANK: // Blanks? This means literal number is explicitly ended.
                should_break = 1;
                break;
        }

        if(should_break == 1) break;
        prev_char = aa_cursor;
    }

    generate_number(tok, str, number_mode);
    return 0;
}

void generate_number(struct token_t *tok, struct string *str, int mode)
{
    tok->type = TOK_LITERAL;
    tok->is_ptr = 1;
    tok->is_dyn_alloc = 1;
    tok->tag = mode;
    tok->value.ptr = (char*)malloc(str->length + 1);

    memcpy(tok->value.ptr, str->str, str->length);
    ((char*)tok->value.ptr)[str->length] = '\0';
}
