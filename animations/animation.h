#ifndef ANIMATION_H
#define ANIMATION_H

#include "Arduino.h"
#include <FastLED.h>

class Animation {
    public:
        Animation(CRGB *leds);
        virtual void start() = 0;
        virtual bool update() = 0;
        uint8_t get_pixel(uint8_t x, uint8_t y);
    protected:
        int HEIGHT = 16;
        int WIDTH = 16;
        CRGB* leds;

};

#endif