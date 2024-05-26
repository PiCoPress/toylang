#include <iostream>
#include "../src/include/tree.h"
#include "gtest/gtest.h"

TEST(val, eight)
{
    node_tree *root = new node_tree();

    node_tree *a = root->append(__token_t::IDT, new int(8));
    a->append(__token_t::IDT, new int(4));
    a->append(__token_t::IDT, new int(2));
    a->append(__token_t::LTR, new int(1));
    
    ASSERT_EQ(*(int*) a->get_value(), 8);
}