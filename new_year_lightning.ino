#include "SnakeGame.hpp"

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

auto BLUE_COLOR = CRGB(0, 0, 255);
auto GREEN_COLOR = CRGB(0, 255, 0);
auto RED_COLOR = CRGB(0, 255, 0);
auto NONE_COLOR = CRGB(0, 0, 0);
} // namespace


void clear()
{
    for (int i = 0; i < NUM_LEDS; ++i)
        leds[i] = NONE_COLOR;
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

        // TODO: map grid to led
        show(grid);

        FastLED.show();

        snake_game.update();

        delay(500);
    }
}

void show(SnakeGame::GameObjects const* const grid)
{
    for (size_t i = 0; i < NUM_LEDS; ++i)
    {
        int left = (i / COLS * COLS);
        int right = (i / COLS + 1) * COLS;
        int index = right - i - 1;

        int target = left + index;

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

        leds[target] = grid[i];
    }
}

void show_flash_screen()
{
    clear();
    FastLED.show();
    delay(500);
}

void loop()
{
    play_snake();
    delay(500);

    while (true)
    {
        show_flash_screen();
        delay(500);
    }
}
