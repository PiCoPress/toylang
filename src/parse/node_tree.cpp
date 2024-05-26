#include "tree.h"

node_tree::node_tree()
{
    parent = nullptr;
    child = std::vector<node_tree *>();
}

node_tree *node_tree::append(node_tree *tr)
{
    tr->parent = this;
    child.push_back(tr);
    tr->parent_index = child.size() - 1;
    return this;
}

node_tree *node_tree::append(__token_t tk, void *val)
{
    node_tree *tr = new node_tree();
    tr->self = tk;
    tr->value = val;
    return append(tr);
}

node_tree *node_tree::insert(__token_t tk, void *val)
{
    node_tree *son = new node_tree();
    son->self = tk;
    son->value = val;

    son->parent = this->parent;
    son->parent_index = this->parent_index;

    son->append(this);
    son->parent->child[son->parent_index] = son;
    return son;
}

node_tree *node_tree::append_set(node_tree *tr)
{
    return append(tr)->child.back();
}

node_tree *node_tree::append_set(__token_t tk, void *val)
{
    return append(tk, val)->child.back();
}

node_tree *node_tree::get_parent()
{
    return parent;
}

std::vector<node_tree*> node_tree::get_children()
{
    return child;
}

__token_t node_tree::get_self_token()
{
    return self;
}

void *node_tree::get_value()
{
    return value;
}

