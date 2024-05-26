#include <vector>
#include "elements.h"

class node_tree
{
    node_tree *parent;
    std::vector<node_tree*> child;
    unsigned int parent_index = 0;
    __token_t self;
    void *value;

public:
    node_tree();
    
    node_tree *append(node_tree *tr);
    node_tree *append(__token_t tk, void *val);

    node_tree *insert(__token_t tk, void *val);

    node_tree *append_set(node_tree *tr);
    node_tree *append_set(__token_t tk, void *val);

    __token_t get_self_token();

    std::vector<node_tree*> get_children();
    node_tree *get_parent();

    void *get_value();

    ~node_tree()
    {
    for (auto i : child)
        delete i;
    }
};