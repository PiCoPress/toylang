#include "bind/ltr.h"

class tl_int8: public ltr<1>
{
public:
    tl_int8(char &c)
    {
        this->val = &c;
    }
};