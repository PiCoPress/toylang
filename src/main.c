#include <stdio.h>
#include "job.h"
#include "ast.h"

int main()
{
    int x, y;
    int a = scanf("%d %d", &x, &y);
    printf("res: %d %d\n", ps(x, y), a);
    return 0;
}