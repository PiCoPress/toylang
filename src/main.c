#include <stdio.h>
#include <string.h>

#include "tokenizers/tokenizer.h"
#include "ast/ast.h"
#include "stringtools.h"

int main()
{
    struct st_token_list tl;
    char *src = "kds2 if def iififif 120_89_3_4 ddee dksla \
    88 asd 1. djsjkdj 1.2 for while do 3_22.4322_43\
    continue for break func return else let %%%}[%^ +-(()\
    if.. <= >= <<= << if(asdv_1234ss!=2";
    int x;

    token_list_init(&tl);

    x = tokenizer(&tl, src, strlen(src));
    printf("ret: %d\n", x);

    for(int i = 0; i < tl.size; ++ i)
    {
        struct token_t *tok = &tl.arr[i];
        if(tok->is_ptr) printf("%s\t%s\ttag: %d\n", STRING_TOKENS[tok->type],
            (char*)tok->value.ptr, tok->tag);
        else printf("%s\t%ld\ttag: %d\n", STRING_TOKENS[tok->type], tok->value.num, tok->tag);
    }
    int h = 129;
    printf("%d: %d %d %d\n", h, get_bit_ceil(h), get_bit_ceil_bs(h), get_bit_ceil_fast(h));

    token_list_delete(&tl);
    return 0;
}
