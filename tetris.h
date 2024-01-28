#ifndef tetris_h
#define tetris_h
#include "Arduino.h"
#include <FastLED.h>

class Tetris {
  public:
    Tetris(CRGB *leds);
    void move(int8_t add_x, int8_t add_y);
    void instant_down();
    void rotate();
  private:
    CRGB* leds;
    uint8_t get_pixel(uint8_t x, uint8_t y);
    bool is_valid(uint8_t row, uint8_t col, uint8_t type, uint8_t state);
    void draw_block(uint8_t x, uint8_t y, uint8_t type, uint8_t state);
    void undraw_block(uint8_t x, uint8_t y, uint8_t type, uint8_t state);
    uint8_t next_blocks[3] = {random(1, 9), random(1, 9), random(1, 9)};
    uint8_t current_block = 0;
    uint8_t current_state = 0;
    int8_t current_x = 4;
    int8_t current_y = 2;
    uint8_t matrix[16][9];
    const int8_t TEMPLATES[8][4][4][2] = {
          {{{-2, 0}, {-1, 0}, {1, 0}, {0, 0}},
          {{0, -2}, {0, -1}, {0, 1}, {0, 0}},
          {{-2, 0}, {-1, 0}, {1, 0}, {0, 0}},
          {{0, -2}, {0, -1}, {0, 1}, {0, 0}}},

          {{{-1, 0}, {1, 0}, {1, -1}, {0, 0}},
          {{-1, -1}, {0, -1}, {0, 1}, {0, 0}},
          {{-1, 0}, {-1, 1}, {1, 0}, {0, 0}},
          {{0, -1}, {0, 1}, {1, 1}, {0, 0}}},

          {{{-1, 0}, {1, 0}, {1, 1}, {0, 0}},
          {{0, -1}, {0, 1}, {1, -1}, {0, 0}},
          {{-1, -1}, {-1, 0}, {1, 0}, {0, 0}},
          {{-1, 1}, {0, -1}, {0, 1}, {0, 0}}},

          {{{-1, 0}, {-1, 1}, {0, 1}, {0, 0}},
          {{-1, 0}, {-1, 1}, {0, 1}, {0, 0}},
          {{-1, 0}, {-1, 1}, {0, 1}, {0, 0}},
          {{-1, 0}, {-1, 1}, {0, 1}, {0, 0}}},

          {{{-1, 0}, {-1, 1}, {0, -1}, {0, 0}},
          {{-1, -1}, {0, -1}, {1, 0}, {0, 0}},
          {{-1, 0}, {-1, 1}, {0, -1}, {0, 0}},
          {{-1, -1}, {0, -1}, {1, 0}, {0, 0}}},

          {{{-1, 0}, {0, -1}, {0, 1}, {0, 0}},
          {{-1, 0}, {0, 1}, {1, 0}, {0, 0}},
          {{0, -1}, {0, 1}, {1, 0}, {0, 0}},
          {{-1, 0}, {0, -1}, {1, 0}, {0, 0}}},

          {{{-1, -1}, {-1, 0}, {0, 1}, {0, 0}},
          {{-1, 1}, {0, 1}, {1, 0}, {0, 0}},
          {{-1, -1}, {-1, 0}, {0, 1}, {0, 0}},
          {{-1, 1}, {0, 1}, {1, 0}, {0, 0}}}
      };
}

#endif