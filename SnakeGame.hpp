#pragma once

#include "Point.hpp"
#include "Snake.hpp"

class SnakeGame
{
public:
    enum GameObjects {
        EMPTY,
        HEAD,
        BODY,
        SHEEP,
    };

    SnakeGame(int8_t columns, int8_t rows);

    void draw(GameObjects* grid);
    void update();
    bool isOver() const;

private:
    const int8_t columns_;
    const int8_t rows_;

    Point sheep_;
    Snake snake_;
    bool is_over_;

    void drawSheep_();
    int8_t getPosition_(Point const& point) const;
    Point getSnakeNextPosition_() const;
    bool out_of_range_(Point const& point) const;
    int get_index_of_(Point const& point) const;
};
