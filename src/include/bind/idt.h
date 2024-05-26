#include <string>
#include "include/tree.h"

typedef unsigned long long int u64;

template<unsigned int t>
struct idt
{
    u64 ptr;
    unsigned int size, type = t;
    bool constant = false;
    node_tree *extra = nullptr;
    std::string name;
};