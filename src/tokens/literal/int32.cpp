#include "bind/ltr.h"

class tl_int32: public ltr<5>
{
public:
    tl_int32(int &num)
    {
        this->val = &num;
    }
};