#include "bind/ltr.h"

// toy variable = 0x12 0x34 0x56 ....
class tl_toy: public ltr<64>
{
    unsigned int size;
public:
    tl_toy(char num[], unsigned int length)
    {
        this->size = length;
        this->val = num;
    }
};