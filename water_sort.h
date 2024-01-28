#ifndef waterSort_h
#define waterSort_h

#include "Arduino.h"
#include <FastLED.h>
#include "stack.h"

class waterSort {
  public:
    waterSort(CRGB *leds);
    uint8_t get_pixel(uint8_t x, uint8_t y);
    void shuffleArray(uint8_t arr[], size_t size);
    void reset_vials();
    void restart_vials();
    void undo_move();
    void draw_vial(uint8_t x, uint8_t y, bool up_down);
    void move_pointers(int add_x, int add_y);
    void choose_vial();
    void is_won();
    void new_level_anim();
    void draw_icon();
  private:
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
    const uint8_t HEIGHT;
    const uint8_t WIDTH;
    const int NUM_LEDS;
    CRGB* leds;
    uint8_t x_pointer;
    uint8_t y_pointer;
    int8_t x_choosen;
    int8_t y_choosen;
    uint8_t moves[5][3];
    uint8_t undo_left;
    Stack vials[12];
    Stack initial_vials[12];

};

#endif