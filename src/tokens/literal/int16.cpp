#include "bind/ltr.h"

class tl_int16: public ltr<3>
{   
public:
    tl_int16(short &num)
    {
        this->val = &num;
    }
};