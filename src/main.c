#include <stdio.h>

#include "tokenizer.h"
#include "ast/ast.h"

int main()
{
    struct st_token_list tl;
    int x, y;
    int a = scanf("%d %d", &x, &y);

    init_token_list(&tl);
    printf("res: %d %d %d\n", a, x, y);

    delete_token_list(&tl);
    return 0;
}