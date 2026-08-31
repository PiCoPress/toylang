#include <stdio.h>

#include "tokenizers/tokenizer.h"
#include "ast/ast.h"
#include "stringtools.h"

int main()
{
    struct st_token_list tl;
    int x;

    init_token_list(&tl);

    x = tokenizer(&tl, "kds2 if def iififif ddee dksla 88 asd");
    printf("ret: %d\n", x);

    for(int i = 0; i < tl.size; ++ i)
    {
        struct token_t *tok = &tl.arr[i];
        if(tok->is_ptr) printf("%s %s\n", STRING_TOKENS[tok->type], (char*)tok->value.ptr);
        else printf("%s %ld\n", STRING_TOKENS[tok->type], tok->value.num);
    }
    int h = 129;
    printf("%d: %d %d %d\n", h, get_ceil_bit(h), get_ceil_bit_fast(h), get_ceil_bit_hw_accel(h));

    delete_token_list(&tl);
    return 0;
}
