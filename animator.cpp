#include "animator.h"

Animator::Animator(CRGB *led_arr) : leds(led_arr) {

}

uint8_t Animator::get_pixel(uint8_t x, uint8_t y) {
  return x*HEIGHT+((x%2==0) ? y : HEIGHT - y - 1);
}

void Animator::start() {
  current_animation = new animSnake1(leds);
}

void Animator::update() {

}

void Animator::draw_icon() {
  fill_solid(leds, 256, CRGB(0, 0, 0));
  for (int i=0; i<4; i++) {
    leds[get_pixel(6 + i, HEIGHT - 5 - i)] = CRGB(40 - i * 10, 40 - i * 10, 180 - i * 10);
  }
  FastLED.show();
}
