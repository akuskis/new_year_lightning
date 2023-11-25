#include "Snake.hpp"

#include "SnakeNode.hpp"

Snake::Snake(int8_t x, int8_t y)
  : head_(new SnakeNode{x, y}),
    tail_(head_)
{
}

Snake::~Snake()
{
    auto* next = head_;
    while (next)
    {
        auto* tmp = next->child();
        delete next;
        next = tmp;
    }
}

SnakeNode const* Snake::head() const
{
    return head_;
}


void Snake::add(Point const& point)
{
    auto node = new SnakeNode(point.getX(), point.getY());
    node->setChild(head_);
    head_->setParent(node);
    head_ = node;
}

void Snake::move(Point const& point)
{
    add(point);

    auto* prev = tail_->parent();
    prev->setChild(nullptr);

    delete tail_;
    tail_ = prev;
}

bool Snake::contains_except_tail(Point const& point) const
{
    // brute force as there is no STL support available... (unordered_set)
    for (auto node = head_; node != tail_; node = node->child())
        if (node->position() == point)
            return true;

    return false;
}

bool Snake::contains(Point const& point) const
{
    for (auto node = head_; node != nullptr; node = node->child())
        if (node->position() == point)
            return true;

    return false;
}
