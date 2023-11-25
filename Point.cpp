#include "Point.hpp"

Point::Point(int8_t x, int8_t y)
  : x_(x),
    y_(y)
{
}

int8_t Point::getX() const
{
    return x_;
}

int8_t Point::getY() const
{
    return y_;
}

bool Point::operator==(Point const& rhs)
{
    return this->x_ == rhs.x_ && this->y_ == rhs.y_;
}

bool Point::operator!=(Point const& rhs)
{
    return !(*this == rhs);
}
