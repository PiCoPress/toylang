#include <stdlib.h>
#include <string.h>

#include "tokenizers/numbers.h"

/*  Do not set str->length directly, because it's a sub-function.
 */
int collect_decimal(struct string *str, char **cursor_ptr, char *const source_end)
{
    char *cursor = *cursor_ptr;
    while(1)
    {
        if(cursor >= source_end) break;

        if(*cursor >= '0' && *cursor <= '9')
            ++ cursor;
        else break;
    }

    append_string(str, *cursor_ptr, cursor - *cursor_ptr); // safer than edit_char
    *cursor_ptr = cursor;
    return 0;
}

/* Returns number_mode if succeed, else return err code */
int collect_number(struct string *str, char **cursor_ptr, char *const source_end)
{
    // mode 0: int      mode 1: non-int
    int number_mode = 0, should_break = 0;
    char prev_char = 0, current_cur_v;
    // current_cur_v: 'a'sterisk 'a'sterisk cursor_ptr

    reset_string(str);
    while(1)
    {
        if(*cursor_ptr >= source_end) break;
        current_cur_v = **cursor_ptr;

        switch(get_char_type(current_cur_v))
        {
            case DECIMAL:
                collect_decimal(str, cursor_ptr, source_end);
                break;

            case ALPHABET_OR_UNDERSCORE:
            {
                // Alphabets or underscores in the decimal context?
                // I will allow underscores, like Python (1_000).
                // But not allow continuous underscores.
                if(current_cur_v == '_')
                {
                    // It's better to use enum based error, but not for now?
                    // __, ._
                    if(prev_char == '_' || prev_char == '.') return -2;
                    // Ignore a single underscore
                    ++ *cursor_ptr;
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
                if(current_cur_v == '.')
                {
                    int test = lookahead(*cursor_ptr, source_end, 1);

                    // Like a "1.2.3", "1.23232..", "1_.".
                    // But float with range? Maybe no.
                    if(number_mode == 1 || prev_char == '_') return -4;

                    if(test == 256) // EOF but float
                    {
                        should_break = 1;
                        number_mode = 1;
                        break;
                    }

                    // Like a ".."
                    if(test == '.')
                    {
                        should_break = 1;
                        break;
                    }

                    number_mode = 1;
                    ++ *cursor_ptr;

                    append_string(str, ".", 1);
                    collect_decimal(str, cursor_ptr, source_end);
                } else should_break = 1;
                break;
            }

            case BLANK: // Blanks: This means literal number is explicitly ended.
                should_break = 1;
                break;
        }

        if(should_break == 1) break;
        prev_char = *(*cursor_ptr - 1);
    }

    return number_mode;
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
