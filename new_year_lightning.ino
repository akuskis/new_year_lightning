#include "SnakeGame.hpp"
#include "snowfall.hpp"

#include <FastLED.h>

#define LED_PIN 2
#define NUM_LEDS 100

CRGB leds[NUM_LEDS];

void setup()
{
    FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);
    FastLED.setMaxPowerInVoltsAndMilliamps(5, 150);
    FastLED.clear();
    FastLED.show();

    randomSeed(analogRead(5));
}

namespace
{
int8_t const COLS = 10;
int8_t const ROWS = 10;
int const SNOWFALL_ITERATIONS = 240;
int const RANDOM_LIGHTS_ITERATIONS = 2400;
int const FIRE_ITERATIONS = 240;

auto BLUE_COLOR = CRGB(0, 0, 255);
auto GREEN_COLOR = CRGB(0, 255, 0);
auto RED_COLOR = CRGB(255, 0, 0);
auto WHITE_COLOR = CRGB(255, 255, 255);
auto NONE_COLOR = CRGB(0, 0, 0);
} // namespace


void clear()
{
    for (int i = 0; i < NUM_LEDS; ++i)
        leds[i] = NONE_COLOR;
}

int convert_to_local(int i)
{
    int left = (i / COLS * COLS);
    int right = (i / COLS + 1) * COLS;
    int index = right - i - 1;

    return (i / COLS % 2) ? i : left + index;
}

void show(SnakeGame::GameObjects const* const grid)
{
    for (size_t i = 0; i < NUM_LEDS; ++i)
    {
        auto const target = convert_to_local(i);

        switch (grid[i])
        {
        case SnakeGame::GameObjects::EMPTY:
            leds[target] = NONE_COLOR;
            break;
        case SnakeGame::GameObjects::HEAD:
            leds[target] = BLUE_COLOR;
            break;
        case SnakeGame::GameObjects::BODY:
            leds[target] = GREEN_COLOR;
            break;
        case SnakeGame::GameObjects::SHEEP:
            leds[target] = RED_COLOR;
            break;
        }
    }
}

void play_snake()
{
    SnakeGame::GameObjects grid[NUM_LEDS];
    SnakeGame snake_game{COLS, ROWS};

    while (!snake_game.isOver())
    {
        for (size_t i = 0; i < NUM_LEDS; ++i)
            grid[i] = SnakeGame::EMPTY;

        snake_game.draw(grid);
        show(grid);

        FastLED.show();
        delay(500);

        snake_game.update();
    }
}

void show(bool* grid)
{
    for (size_t i = 0; i < NUM_LEDS; ++i)
    {
        auto const target = convert_to_local(i);

        leds[target] = grid[i] ? WHITE_COLOR : NONE_COLOR;
    }
}

void run_snowfall()
{
    bool grid[NUM_LEDS] = {false};

    for (size_t count = 0; count != SNOWFALL_ITERATIONS; ++count)
    {
        snowfall::simulate_snowfall(grid, COLS, ROWS);
        show(grid);

        FastLED.show();
        delay(500);
    }
}

void run_random_lights()
{
    for (size_t count = 0; count != RANDOM_LIGHTS_ITERATIONS; ++count)
    {
        leds[random(NUM_LEDS)] = CRGB(random(256), random(256), random(256));
        FastLED.show();
        delay(50);
    }
}

void loop()
{
    while (true)
    {
        run_random_lights();

        run_snowfall();

        play_snake();
    }
}
