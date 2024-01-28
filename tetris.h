#ifndef tetris_h
#define tetris_h
#include "Arduino.h"
#include <FastLED.h>
#include "stack.h"

class Tetris {
  public:
    Tetris(CRGB *leds);
    void game_frame();
    void move(int8_t add_x, int8_t add_y);
    void instant_down();
    void rotate();
    void new_game();
    void draw_icon();
  private:
    const uint8_t HEIGHT = 16;
    const uint8_t WIDTH = 16;
    const int NUM_LEDS = HEIGHT * WIDTH;
    CRGB* leds;
    uint8_t get_pixel(uint8_t x, uint8_t y);
    bool is_valid(uint8_t row, uint8_t col, uint8_t type, uint8_t state);
    void draw_block(uint8_t x, uint8_t y, uint8_t type, uint8_t state);
    void undraw_block(uint8_t x, uint8_t y, uint8_t type, uint8_t state);
    void draw_matrix(bool block_redraw);
    uint8_t next_blocks[3] = {random(1, 8), random(1, 8), random(1, 8)};
    uint8_t current_block = random(1, 8);
    uint8_t current_state = 0;
    int8_t current_x = 4;
    int8_t current_y = 2;
    bool is_block_placed = false;
    int frame_counter = 0;
    uint8_t matrix[16][9];
    Stack rows_to_del;
    const CRGB colors[8] = {
      CRGB(0, 0, 0),
      CRGB(0, 0, 255),
      CRGB(255, 64, 0),
      CRGB(96, 0, 255),
      CRGB(255, 255, 0),
      CRGB(255, 0, 64),
      CRGB(0, 255, 0),
      CRGB(255, 0, 0)
    };
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
};

#endif