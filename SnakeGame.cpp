#include "SnakeGame.hpp"

#include "SnakeNode.hpp"

#include "Arduino.h"

namespace
{
Point randomPoint(int8_t columns, int8_t rows)
{
    return Point{random(columns), random(rows)};
}
} // namespace

SnakeGame::SnakeGame(int8_t columns, int8_t rows)
  : columns_(columns),
    rows_(rows),
    sheep_(randomPoint(columns, rows)),
    snake_{columns / 2, rows / 2},

    is_over_(false)
{
    while (snake_.contains(sheep_))
        sheep_ = randomPoint(columns_, rows_);
}

void SnakeGame::draw(GameObjects* grid)
{
    auto* snake_node = snake_.head();
    grid[getPosition_(snake_node->position())] = GameObjects::HEAD;
    snake_node = snake_node->child();

    while (snake_node != nullptr)
    {
        grid[getPosition_(snake_node->position())] = GameObjects::BODY;
        snake_node = snake_node->child();
    }

    grid[getPosition_(sheep_)] = GameObjects::SHEEP;
}

void SnakeGame::update()
{
    Point next_point = getSnakeNextPosition_();

    if (next_point == sheep_)
    {
        snake_.add(next_point);
        auto next_sheep = randomPoint(columns_, rows_);
        while (snake_.contains(next_sheep))
            next_sheep = randomPoint(columns_, rows_);

        sheep_ = next_sheep;
    }
    else if (snake_.contains_except_tail(next_point) || out_of_range_(next_point))
    {
        is_over_ = true;
    }
    else
    {
        snake_.move(next_point);
    }
}

bool SnakeGame::isOver() const
{
    return is_over_;
}

int8_t SnakeGame::getPosition_(Point const& point) const
{
    return point.getX() + point.getY() * columns_;
}

// dummy implementation as no STL available on Arduino out of box
// do not want to waste time, rewrite if Arduino will be replaced by Teensy
Point SnakeGame::getSnakeNextPosition_() const
{
    auto const snake_head = snake_.head()->position();

    // fill the grid
    int grid[columns_ * rows_] = {0};
    for (auto const* it = snake_.head(); it; it = it->child())
        grid[get_index_of_(it->position())] = 1;

    Point queue[columns_ * rows_];
    queue[0] = sheep_;
    size_t next_index = 1;

    Point const directions[] = {Point{-1, 0}, Point{1, 0}, Point{0, -1}, Point{0, 1}};
    size_t const directions_count = sizeof(directions) / sizeof(directions[0]);

    for (size_t i = 0; i < next_index; ++i)
    {
        for (size_t direction_index = 0; direction_index < directions_count; ++direction_index)
        {
            Point pos{queue[i].getX() + directions[direction_index].getX(),
                      queue[i].getY() + directions[direction_index].getY()};

            if (out_of_range_(pos))
                continue;

            int pos_index = get_index_of_(pos);

            if (pos == snake_head)
                return queue[i];

            if (grid[pos_index])
                continue;

            grid[pos_index] = true;
            queue[next_index++] = pos;
        }
    }

    for (int direction_index = 0; direction_index < directions_count; ++direction_index)
    {
        Point pos{snake_head.getX() + directions[direction_index].getX(),
                  snake_head.getY() + directions[direction_index].getY()};

        if (!snake_.contains_except_tail(pos) && !out_of_range_(pos))
            return pos;
    }

    return Point{snake_head.getX(), snake_head.getY() - 1};
}

bool SnakeGame::out_of_range_(Point const& point) const
{
    return point.getX() < 0 || point.getX() >= columns_ || point.getY() < 0 || point.getY() >= rows_;
}

int SnakeGame::get_index_of_(Point const& point) const
{
    return point.getX() + point.getY() * columns_;
}
