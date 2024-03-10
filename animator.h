#ifndef animator_h
#define animator_h
#include "animations/animation.h"
#include "animations/snake_1.h"
#include "Arduino.h"
#include <FastLED.h>

class Animator {
  public:
    Animator(CRGB *leds);
    void start();
    void update();
    void draw_icon();
  private:
    const uint8_t HEIGHT = 16;
    const uint8_t WIDTH = 16;
    const int NUM_LEDS = HEIGHT * WIDTH;
    CRGB* leds;
    uint8_t get_pixel(uint8_t x, uint8_t y);
    Animation* current_animation;
};

#endif
