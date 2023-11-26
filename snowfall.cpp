#include "snowfall.hpp"

#include <Arduino.h>


namespace snowfall
{
void simulate_snowfall(bool* grid, int columns, int rows)
{
    for (int y = rows - 1; y > 0; --y)
    {
        for (int i = y * columns; i < (y + 1) * columns; ++i)
            grid[i] = false;

        for (int i = y * columns; i < (y + 1) * columns; ++i)
        {
            if (grid[i - columns])
            {
                int di = random(3) - 1;
                int ii = min(max((y)*columns, i + di), (y + 1) * columns - 1);
                grid[ii] = true;
            }
        }
    }

    for (int x = 0; x < columns; ++x)
        grid[x] = false;

    for (int x = random(4) - 1; x >= 0; --x)
        grid[random(columns) - 1] = true;
}
} // namespace snowfall
