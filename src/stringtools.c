#include <stdlib.h>
#include <string.h>

#include "stringtools.h"

void create_string(struct string *str)
{
    str->mult = 16;
    str->capacity = 16;
    str->length = 0;
    str->str = (char*)malloc(16);
}

void destroy_string(struct string *str)
{
    if(str->str != NULL)
    {
        free(str->str);
        str->str = NULL;
    }
}

void append_string(struct string *dest, const char *src, int src_len)
{
    writeat_string(dest, src, src_len, dest->length);
}

void writeat_string(struct string *dest, const char *src, int src_len, int dest_pos)
{
    if(dest_pos + src_len >= dest->capacity)
    {
        adjust_mult(dest, dest_pos, src_len);
        dest->capacity += dest->mult;
        dest->str = (char*)realloc(dest->str, dest->capacity);
    }
    strncpy(dest->str + dest_pos, src, src_len);
    dest->length = dest_pos + src_len;
}

void reset_string(struct string *str)
{
    str->length = 0;
}

inline void edit_char(struct string *str, int idx, char c)
{
    str->str[idx] = c;
}

inline void adjust_mult(struct string *str, int str_pos, int src_len)
{
    int *const mult_ptr = &str->mult;

    if((*mult_ptr + str->capacity) < str_pos + src_len)
        *mult_ptr = get_bit_ceil_fast(src_len);
    else
    {
        if(*mult_ptr < 512) *mult_ptr *= 2;
        if(*mult_ptr > 512) *mult_ptr = 512;
    }
}

inline unsigned int get_bit_ceil(int x)
{
    unsigned int mul = 1;
    while(mul < x) mul <<= 1;
    return mul;
}

/*  Uses binary search
 */
inline unsigned int get_bit_floor_bs(int x)
{
    unsigned int sum = 1;
    int mul = sizeof(int) * 8 / 2, x1;

    while(mul)
    {
        x1 = x >> mul;
        if(x1 >= 1)
        {
            sum <<= mul;
            if(x1 == 1) return sum;
            x = x1;
        }
        mul >>= 1;
    }
    return sum;
}

inline unsigned int get_bit_ceil_bs(int x)
{
    unsigned int r = get_bit_floor_bs(x);
    return (x != r)? (r << 1): x;
}

inline unsigned int get_bit_ceil_fast(int x)
{
    -- x;
    return x? 1U << (32 - __builtin_clz(x)): 1U;
}
