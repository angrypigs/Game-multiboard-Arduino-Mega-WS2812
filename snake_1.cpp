#include "snake_1.h"

void animSnake1::start() {
    fill_solid(leds, 256, CRGB::Black);
    counter = 0;
    limit = 15;
    direction = 0;
}

bool animSnake1::update() {
    switch (direction) {
        case 0:
            leds[get_pixel(counter, HEIGHT - 1 - limit)] = (limit % 2 == 0) ? CRGB(255, 0, 0) : CRGB(0, 255, 0);
            break;
        case 1:
            leds[get_pixel(limit, counter)] = (limit % 2 == 0) ? CRGB(255, 0, 0) : CRGB(0, 255, 0);
            break;
        case 2:
            leds[get_pixel(HEIGHT - 1 - counter, limit)] = (limit % 2 == 0) ? CRGB(255, 0, 0) : CRGB(0, 255, 0);
            break;
        case 3:
            leds[get_pixel(HEIGHT - 1 - limit, HEIGHT - 1 - counter)] = (limit % 2 == 0) ? CRGB(255, 0, 0) : CRGB(0, 255, 0);
            break;
    }
    FastLED.show();
    counter++;
    if (counter == limit) {
        direction = (direction + 1) % 4;
        counter = HEIGHT - 1 - limit;
        if (direction == 0) {
            limit--;
            if (limit == 7) {
                return true;
            }
        }
    }
    return false;
}   
