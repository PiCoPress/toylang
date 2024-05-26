#include "bind/ltr.h"

class tl_uint8: public ltr<0>
{
public:
    tl_uint8(unsigned char &num)
    {
        this->val = &num;
    }
};