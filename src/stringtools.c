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
    if(dest->length + src_len >= dest->capacity)
    {
        adjust_mult(dest, src_len);
        dest->capacity += dest->mult;
        dest->str = (char*)realloc(dest->str, dest->capacity);
    }
    strncpy(dest->str + dest->length, src, src_len);
    dest->length += src_len;
}

inline void edit_char(struct string *str, int idx, char c)
{
    str->str[idx] = c;
}

inline void adjust_mult(struct string *str, int src_len)
{
    int *const mult_ptr = &str->mult;

    if((*mult_ptr + str->capacity) < str->length + src_len) *mult_ptr = get_ceil_bit(src_len);
    if(*mult_ptr < 512) *mult_ptr *= 2;
    if(*mult_ptr > 512) *mult_ptr = 512;
}

inline unsigned int get_ceil_bit(int x)
{
    unsigned int mul = 1;
    while(mul < x) mul <<= 1;
    return mul;
}

// maybe fast...?
inline unsigned int get_floor_bit_fast(int x)
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

inline unsigned int get_ceil_bit_fast(int x)
{
    unsigned int r = get_floor_bit_fast(x);
    return (x != r)? (r << 1): x;
}

inline unsigned int get_ceil_bit_hw_accel(int x)
{
    -- x;
    return x? 1U << (32 - __builtin_clz(x)): 1U;
}
