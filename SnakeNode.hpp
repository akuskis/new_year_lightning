#pragma once

#include "Point.hpp"

#include "stdint.h"

class SnakeNode
{
public:
    SnakeNode(int8_t x, int8_t y);

    SnakeNode* child() const;
    void setChild(SnakeNode* node);

    SnakeNode* parent() const;
    void setParent(SnakeNode* node);

    Point position() const;

private:
    SnakeNode* parent_;
    SnakeNode* child_;
    Point position_;
};
