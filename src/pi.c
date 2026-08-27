#include "job.h"

int ps(int a, int b)
{
    if(a > b)
    {
        return b * 2;
    }
    else
    {
        if(b != 0)
            return a / b;
        
        else return 6;
    }
}