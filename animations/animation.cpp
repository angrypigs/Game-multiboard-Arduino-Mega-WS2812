#include "animation.h"

Animation::Animation(CRGB *led_arr) : leds(led_arr) {

}

uint8_t Animation::get_pixel(uint8_t x, uint8_t y) {
  return x*HEIGHT+((x%2==0) ? y : HEIGHT - y - 1);
}