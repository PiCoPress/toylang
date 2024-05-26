#include <string>
#include <vector>
#include "elements.h"

template<char *s>
struct kwd
{
    std::string name = s;
    std::vector<__token_t> rule;
};