#include "bind/ltr.h"

class tl_string: public ltr<17>
{
public:
    tl_string(char str[])
    {
        this->val = str;
    }
};