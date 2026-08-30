#include <stdio.h>

#include "tokenizer.h"
#include "ast/ast.h"

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
        if(tok->is_ptr) printf("%d %s\n", tok->type, (char*)tok->value.ptr);
        else printf("%s %ld\n", STRING_TOKENS[tok->type], tok->value.num);
    }

    delete_token_list(&tl);
    return 0;
}
