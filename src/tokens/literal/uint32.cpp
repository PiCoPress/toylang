#include "bind/ltr.h"

class tl_uint32: public ltr<4>
{
public:
    tl_uint32(unsigned int &num)
    {
        this->val = &num;
    }
};