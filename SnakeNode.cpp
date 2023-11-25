#include "SnakeNode.hpp"

SnakeNode::SnakeNode(int8_t x, int8_t y)
  : parent_(nullptr),
    child_(nullptr),
    position_(x, y)
{
}

SnakeNode* SnakeNode::child() const
{
    return child_;
}

void SnakeNode::setChild(SnakeNode* node)
{
    child_ = node;
}

SnakeNode* SnakeNode::parent() const
{
    return parent_;
}

void SnakeNode::setParent(SnakeNode* node)
{
    parent_ = node;
}

Point SnakeNode::position() const
{
    return position_;
}
