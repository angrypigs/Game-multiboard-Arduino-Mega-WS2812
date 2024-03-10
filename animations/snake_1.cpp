#include "snake_1.h"

void animSnake1::start() {

}

bool animSnake1::update() {
    switch (direction) {
        case 0:
            leds[get_pixel(counter, HEIGHT - 1 - limit)] = CRGB(255, 0, 0);
            break;
        case 1:
            leds[get_pixel(limit, counter)] = CRGB(255, 0, 0);
            break;
        case 2:
            leds[get_pixel(HEIGHT - 1 - counter, limit)] = CRGB(255, 0, 0);
            break;
        case 3:
            leds[get_pixel(HEIGHT - 1 - limit, HEIGHT - 1 - counter)] = CRGB(255, 0, 0);
            break;
    }
    FastLED.show();
    counter++;
    if (counter == limit) {
        direction = (direction + 1 ) % 4;
        counter = 0;
        if (direction == 0) {
            limit--;
            if (limit == 3) {
                return true;
            }
        }
    }
    return false;
}   