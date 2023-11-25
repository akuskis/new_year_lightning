#pragma once

#include "Point.hpp"

#include "stdint.h"

class SnakeNode;

class Snake
{
public:
    Snake(int8_t x, int8_t y);
    ~Snake();

    SnakeNode const* head() const;
    void add(Point const& point);
    void move(Point const& point);

    bool contains_except_tail(Point const& point) const;
    bool contains(Point const& point) const;

private:
    SnakeNode* head_;
    SnakeNode* tail_;
};
