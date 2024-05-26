#include "bind/ltr.h"

class tl_uint16: public ltr<2>
{
public:
    tl_uint16(unsigned short &num)
    {
        this->val = &num;
    }
};