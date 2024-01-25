#include "water_sort.h"

waterSort::waterSort(CRGB *led_arr) 
  : leds(led_arr), 
  HEIGHT(16), 
  WIDTH(16), 
  NUM_LEDS(HEIGHT * WIDTH),
  x_pointer(0), 
  y_pointer(0), 
  x_choosen(-1), 
  y_choosen(-1), 
  undo_left(5) {
    for (int i = 0; i < 5; ++i) {
      for (int j = 0; j < 3; ++j) {
        moves[i][j] = 0;
      }
    }
}

uint8_t waterSort::get_pixel(uint8_t x, uint8_t y) {
  return x*HEIGHT+((x%2==0) ? y : HEIGHT - y - 1);
}

void waterSort::shuffleArray(uint8_t *arr, size_t size) {
    // Tasowanie czwórek liczb
  for (size_t i = 0; i < size; i += 4) {
    uint8_t temp[4] = {arr[i], arr[i + 1], arr[i + 2], arr[i + 3]};

    // Tasowanie czwórki
    for (int j = 3; j > 0; j--) {
      int k = random(0, j + 1);
      uint8_t t = temp[j];
      temp[j] = temp[k];
      temp[k] = t;
    }

    // Przypisanie tasowanej czwórki z powrotem do tablicy
    arr[i] = temp[0];
    arr[i + 1] = temp[1];
    arr[i + 2] = temp[2];
    arr[i + 3] = temp[3];
  }

  // Dodatkowe tasowanie całej tablicy
  for (size_t i = size - 1; i > 0; i--) {
    size_t j = random(0, i + 1);
    uint8_t t = arr[i];
    arr[i] = arr[j];
    arr[j] = t;
  }
}

void waterSort::reset_vials() {
    for (int i=0; i<12; i++) {
    while (vials[i].top != 0) {
      vials[i].pop();
    }
  }
  uint8_t temp_arr[40];
  for (int i = 0; i < 40; i++) {
    temp_arr[i] = (i%10)+1;
  }
  shuffleArray(temp_arr, 40);
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 4; j++) {
      vials[i].push(temp_arr[i*4+j]);
    }
  }
  for (int i=0; i<12; i++) {
    initial_vials[i] = vials[i];
  }
  for (int i=0; i<5; i++) {
    for (int j=0; j<3; j++) {
      moves[i][j] = 0;
    }
  }
  undo_left = 5;
  for (int i=0; i<5; i++) {
    leds[get_pixel(14, 1+2*i)] = CRGB(128, 128, 128);
  }
  for (int i=0; i<2; i++) {
    for (int j=0; j<6; j++) {
      draw_vial(j, i, false);
    }
  }
  move_pointers(0, 0);
  FastLED.show();
}

void waterSort::restart_vials() {
  for (int i=0; i<2; i++) {
    for (int j=0; j<6; j++) {
      vials[i*6+j] = initial_vials[i*6+j];
      draw_vial(j, i, false);
    }
  }
  for (int i=0; i<5; i++) {
    for (int j=0; j<3; j++) {
      moves[i][j] = 0;
    }
  }
  undo_left = 5;
  for (int i=0; i<5; i++) {
    leds[get_pixel(14, 1+2*i)] = CRGB(128, 128, 128);
  }
  FastLED.show();
}

void waterSort::undo_move() {
  if (undo_left > 0 && moves[4][2] != 0) {
    uint8_t a = moves[4][0];
    uint8_t b = moves[4][1];
    for (int i=0; i<moves[4][2]; i++) {
      vials[a].push(vials[b].pop());
    }
    draw_vial(a%6, a/6, false);
    draw_vial(b%6, b/6, false);
    for (int i=4; i>0; i--) {
      for (int j=0; j<3; j++) {
        moves[i][j] = moves[i-1][j];
      }
    }
    moves[0][0] = 0;
    moves[0][1] = 0;
    moves[0][2] = 0;
    undo_left--;
    leds[get_pixel(14, 1+2*undo_left)] = CRGB(0, 0, 0);
    FastLED.show();
  }
}

void waterSort::draw_vial(uint8_t x, uint8_t y, bool up_down) {
  int8_t pad = (up_down) ? -1 : 0;
  for (int i=0; i<4; i++) {
    uint8_t n = get_pixel(1+2*x, 2+8*y+i+pad);
    leds[n] = colors[vials[y*6+x].table[3-i]];
  }
  leds[get_pixel(1+2*x, 6+8*y+pad)] = CRGB(63, 63, 63);
  if (up_down) {
    leds[get_pixel(1+2*x, 6+8*y)] = CRGB(0, 0, 0);
  }
  else {
    leds[get_pixel(1+2*x, 1+8*y)] = CRGB(0, 0, 0);
  }
}

void waterSort::move_pointers(int add_x, int add_y) {
  leds[get_pixel(1+2*x_pointer, 7+8*y_pointer)] = CRGB(0, 0, 0);
  x_pointer = (x_pointer + add_x + 6)%6;
  y_pointer = (y_pointer + add_y + 2)%2;
  leds[get_pixel(1+2*x_pointer, 7+8*y_pointer)] = CRGB(255, 255, 255);
  FastLED.show();
}

void waterSort::choose_vial() {
  if (x_choosen == -1 && y_choosen == -1) {
    if (vials[y_pointer*6+x_pointer].top > 0) {
      x_choosen = x_pointer;
      y_choosen = y_pointer;
      draw_vial(x_choosen, y_choosen, true);
    }
  }
  else {
    uint8_t a = y_choosen*6+x_choosen;
    uint8_t b = y_pointer*6+x_pointer;
    if ((vials[a].top_element() == vials[b].top_element() && vials[b].top < 4) || vials[b].top == 0) {
      int i = vials[a].top - 1;
      int counter = 0;
      while (i >= 0 && (vials[a].table[i] == vials[a].top_element())) {
        counter++;
        i--;
      }
      int minimum = (counter > (4 - vials[b].top)) ? 4 - vials[b].top : counter;
      for (int i=0; i<minimum; i++) {
        vials[b].push(vials[a].pop());
      }
      draw_vial(x_pointer, y_pointer, false);
      for (int i=0; i<4; i++) {
        for (int j=0; j<3; j++) {
          moves[i][j] = moves[i+1][j];
        }
      }
      moves[4][0] = a;
      moves[4][1] = b;
      moves[4][2] = minimum;
    }
    draw_vial(x_choosen, y_choosen, false);
    x_choosen = -1;
    y_choosen = -1;
    is_won();
  }
  FastLED.show();
}

void waterSort::is_won() {
  for (int i=0; i<12; i++) {
    for (int j=1; j<4; j++) {
      uint8_t n = vials[i].table[0];
      if (vials[i].table[j] != n) {
        return;
      }
    }
  }
  new_level_anim();
  reset_vials();
}

void waterSort::new_level_anim() {
  leds[0] = CRGB(255, 0, 0);
  for (int i=1; i<256; i++) {
    leds[i] = CRGB(255, 0, 0);
    leds[i - 1] = CRGB(0, 0, 0);
    FastLED.show();
    delay(8);
  }
  leds[255] = CRGB(0, 0, 0);
  FastLED.show();
}

