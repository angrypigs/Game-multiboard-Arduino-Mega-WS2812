#include "tetris.h"

Tetris::Tetris(CRGB *led_arr) : leds(led_arr) {
  for (int i=0; i<16; i++) {
    for (int j=0; j<9; j++) {
      matrix[i][j] = 0;
    }
  }
}

uint8_t Tetris::get_pixel(uint8_t x, uint8_t y) {
  return x*HEIGHT+((x%2==0) ? y : HEIGHT - y - 1);
}

bool Tetris::is_valid(uint8_t row, uint8_t col, uint8_t type, uint8_t state) {
  for (int i=0; i<4; i++) {
    int8_t a = row + TEMPLATES[type - 1][state][i][0];
    int8_t b = col + TEMPLATES[type - 1][state][i][1];
    if ((a > 15) || (b < 0) || (b > 8) || matrix[a][b] != 0) {
      return false;
    }
  }
  return true;
}

void Tetris::draw_block(uint8_t x, uint8_t y, uint8_t type, uint8_t state) {
  for (int i=0; i<4; i++) {
    uint8_t x_add = x + TEMPLATES[type - 1][state][i][1];
    uint8_t y_add = y + TEMPLATES[type - 1][state][i][0];
    leds[get_pixel(x_add, y_add)] = colors[type];
  }
}

void Tetris::undraw_block(uint8_t x, uint8_t y, uint8_t type, uint8_t state) {
  for (int i=0; i<4; i++) {
    uint8_t x_add = x + TEMPLATES[type - 1][state][i][1];
    uint8_t y_add = y + TEMPLATES[type - 1][state][i][0];
    leds[get_pixel(x_add, y_add)] = CRGB(0, 0, 0);
  }
}

void Tetris::draw_matrix(bool block_redraw) {
  for (int i=0; i<16; i++) {
    for (int j=0; j<9; j++) {
      leds[get_pixel(j + 1, i)] = colors[matrix[i][j]];
    }
  }
  if (block_redraw) {
    draw_block(current_x + 1, current_y, current_block, current_state);
  }
  FastLED.show();
}

void Tetris::new_game() {
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  for (int i=0; i<16; i++) {
    for (int j=0; j<9; j++) {
      matrix[i][j] = 0;
    }
  }
  rows_to_del.top = 0;
  current_block = random(1, 8);
  current_x = 4;
  current_y = 2;
  current_state = 0;
  is_block_placed = false;
  frame_counter = 0;
  for (int i=0; i<16; i++) {
    leds[get_pixel(0, i)] = CRGB(63, 63, 63);
    leds[get_pixel(10, i)] = CRGB(63, 63, 63);
  }
  for (int i=0; i<3; i++) {
    next_blocks[i] = random(1, 8);
    draw_block(13, 3 + 5 * i, next_blocks[i], 0);
  }
  draw_block(current_x + 1, current_y, current_block, 0);
  FastLED.show();
}

void Tetris::game_frame() {
  if (frame_counter % 20 == 0) {
    if (is_valid(current_y + 1, current_x, current_block, current_state)) {
      undraw_block(current_x + 1, current_y, current_block, current_state);
      current_y++;
      draw_block(current_x + 1, current_y, current_block, current_state);
      is_block_placed = false;
      FastLED.show();
    }
    else {
      is_block_placed = true;
    }
    if (is_block_placed) {
      for (int i=0; i<4; i++) { // put block in matrix
        int8_t a = current_y + TEMPLATES[current_block - 1][current_state][i][0];
        int8_t b = current_x + TEMPLATES[current_block - 1][current_state][i][1];
        matrix[a][b] = current_block;
      }
      for (int8_t i=15; i>=0; i--) { //check for full rows (max 4)
        bool flag = true;
        for (int8_t j=0; j<9; j++) {
          if (matrix[i][j] == 0) {
            flag = false;
            break;
          }
        }
        if (flag) { // if there's any full rows, add them to stack and empty them
          rows_to_del.push(i);
          for (int j=0; j<9; j++) {
            matrix[i][j] = 0;
          }
        }
      }
      for (int i=0; i<3; i++) {
        undraw_block(13, 3 + 5 * i, next_blocks[i], 0);
      }
      current_block = next_blocks[0]; // push next blocks forward and generate next one
      next_blocks[0] = next_blocks[1];
      next_blocks[1] = next_blocks[2];
      next_blocks[2] = random(1, 8);
      for (int i=0; i<3; i++) {
        draw_block(13, 3 + 5 * i, next_blocks[i], 0);
      }
      current_x = 4;
      current_y = 2;
      current_state = 0;
      draw_matrix(true);
    }
  }

  else if ((frame_counter % 3 == 0) && (rows_to_del.top != 0)) {
    uint8_t row = rows_to_del.pop();
    for (int i=row; i>0; i--) {
      for (int j=0; j<9; j++) {
        matrix[i][j] = matrix[i - 1][j];
      }
    }
    draw_matrix(true);
  }
  frame_counter = (frame_counter + 1) % 60;
}

void Tetris::move(int8_t add_x, int8_t add_y) {
  if (is_valid(current_y + add_y, current_x + add_x, current_block, current_state)) {
    undraw_block(current_x + 1, current_y, current_block, current_state);
    current_x = current_x + add_x;
    current_y = current_y + add_y;
    draw_block(current_x + 1, current_y, current_block, current_state);
    FastLED.show();
  }
}

void Tetris::rotate() {
  const int8_t rotations[] = {0, 1, 2, -1};
  int8_t temp_state = (current_state + 1) % 4;
  bool flag = false;
  int8_t a = 0;
  for (int8_t offset : rotations) {
    if (is_valid(current_y, current_x + offset, current_block, temp_state)) {
      flag = true;
      a = offset;
      break;
    }
  }
  if (flag) {
    undraw_block(current_x + 1, current_y, current_block, current_state);
    current_state = temp_state;
    current_x = current_x + a;
    draw_block(current_x + 1, current_y, current_block, current_state);
    FastLED.show();
  } 
}

void Tetris::instant_down() {
  undraw_block(current_x + 1, current_y, current_block, current_state);
  while (is_valid(current_y + 1, current_x, current_block, current_state)) {
    current_y++;
  }
  draw_block(current_x + 1, current_y, current_block, current_state);
  is_block_placed = true;
  FastLED.show();
}

void Tetris::draw_icon() {
  fill_solid(leds, NUM_LEDS, CRGB(0, 0, 0));
  draw_block(6, 5, 3, 1);
  draw_block(6, 9, 6, 0);
  draw_block(8, 8, 5, 1);
  draw_block(9, 8, 1, 0);
  FastLED.show();
}
