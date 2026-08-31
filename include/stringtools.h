#ifndef __STRING_TOOLS_H
#define __STRING_TOOLS_H

/* Processes dynamic-sized string - no fail */

struct string {
    int mult;
    int capacity;
    int length;
    char *str;
};

void create_string(struct string *str);
void destroy_string(struct string *str);

void append_string(struct string *dest, const char *src, int src_len);

void edit_char(struct string *str, int idx, char c);
void adjust_mult(struct string *str, int size);

unsigned int get_bit_ceil(int x);
unsigned int get_bit_floor_bs(int x);
unsigned int get_bit_ceil_bs(int x);
unsigned int get_bit_ceil_fast(int x);

#endif
