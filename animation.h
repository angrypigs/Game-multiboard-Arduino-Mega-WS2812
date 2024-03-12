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
        const CRGB colors[11] = {
          CRGB(0, 0, 0),
          CRGB(255, 0, 0),   // Czerwony
          CRGB(255, 64, 0),  // Pomarańczowy
          CRGB(255, 255, 0), // Żółty
          CRGB(0, 255, 0),   // Zielony
          CRGB(0, 192, 255), // Cyjan
          CRGB(0, 0, 255),   // Niebieski
          CRGB(96, 0, 255),  // Fioletowy
          CRGB(255, 0, 223), // Magenta
          CRGB(255, 0, 64),  // Różowy
          CRGB(255, 32, 32)  // Jasnoczerwony
        };
        int HEIGHT = 16;
        int WIDTH = 16;
        CRGB *leds;

};

#endif
