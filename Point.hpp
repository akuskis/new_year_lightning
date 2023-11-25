#pragma once

#include <stdint.h>

struct Point
{
public:
    Point(int8_t x = -1, int8_t y = -1);

    int8_t getX() const;
    int8_t getY() const;

    bool operator==(Point const& rhs);
    bool operator!=(Point const& rhs);

private:
    int8_t x_;
    int8_t y_;
};
