#include "water_sort.h"
#include <FastLED.h>

#define LED_PIN 23

#define VR_X 0
#define VR_Y 1
#define VR_SW 8
#define SW_SELECT 7 // Select
#define SW_START 6 // Start
#define SW_X 5 // blue left
#define SW_Y 2 // yellow top
#define SW_A 4 // yellow bottom
#define SW_B 3 // blue right
#define NUM_SWITCHES 7

uint8_t swPins[NUM_SWITCHES] = {VR_SW, SW_SELECT, SW_START, SW_X, SW_Y, SW_A, SW_B};
uint8_t swStatus[NUM_SWITCHES] = {0, 0, 0, 0, 0, 0, 0};
uint8_t swFlags[NUM_SWITCHES] = {0, 0, 0, 0, 0, 0, 0};
uint16_t joy[2] = {0, 0};

void doInput() {
  int x = analogRead(0);
  int y = analogRead(1);
  joy[0] = map(x, 0, 691, 0, 100);
  joy[1] = map(y, 0, 691, 0, 100);
  for (int i = 0; i < NUM_SWITCHES; i++) {
    swStatus[i] = ((digitalRead(swPins[i])) ? (0) : (1));
  }
}

void doShowInfo() {
  Serial.print("X: ");
  Serial.print(joy[0]);
  Serial.print(" Y: ");
  Serial.print(joy[1]);
  Serial.print(" Sw: ");
  for (int i = 0; i < NUM_SWITCHES; i++) {
    Serial.print(swStatus[i]);
    if (i < (NUM_SWITCHES - 1)) {
      Serial.print(":");
    }
  }
  Serial.println();
}


bool flag_left = true;
bool flag_right = true;
bool flag_up = true;
bool flag_down = true;

unsigned long previous_millis = 0;

const uint8_t HEIGHT = 16;
const uint8_t WIDTH = 16;
const int NUM_LEDS = HEIGHT * WIDTH;
CRGB leds[NUM_LEDS];

waterSort watersort = waterSort(leds);

uint8_t current_game = 1;

void handle_input(uint8_t index) {
  switch (current_game) {
    case 1:
      switch (index) {
        case 0:
          watersort.choose_vial();
          break;
        case 1:
          break;
        case 2:
          break;
        case 3:
          break;
        case 4:
          watersort.undo_move();
          break;
        case 5:
          watersort.restart_vials();
          break;
        case 6:
          break;
        case 7:
          watersort.move_pointers(-1, 0);
          break;
        case 8:
          watersort.move_pointers(1, 0);
          break;
        case 9:
          watersort.move_pointers(0, -1);
          break;
        case 10:
          watersort.move_pointers(0, 1);
          break;
        case 11:
          break;
      }
      break;
  }
}

void setup() {
  Serial.begin(115200);
  randomSeed(analogRead(A15));
  for (int i = 0; i < NUM_SWITCHES; i++) {
    pinMode( swPins[i], INPUT );
    digitalWrite( swPins[i], HIGH );
  }
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(10);
  watersort.reset_vials();
  FastLED.show();
}

void loop() {
  doInput();
  if (joy[0] < 10 && flag_left && flag_up && flag_down) {
    flag_left = false;
    handle_input(7);
  }
  else if (joy[0] > 10 && !flag_left) {
    flag_left = true;
  }

  if (joy[0] > 90 && flag_right && flag_up && flag_down) {
    flag_right = false;
    handle_input(8);
  }
  else if (joy[0] < 90 && !flag_right) {
    flag_right = true;
  }

  if (joy[1] < 10 && flag_down && flag_left && flag_right) {
    flag_down = false;
    handle_input(9);
  }
  else if (joy[1] > 10 && !flag_down) {
    flag_down = true;
  }

  if (joy[1] > 90 && flag_up && flag_left && flag_right) {
    flag_up = false;
    handle_input(10);
  }
  else if (joy[1] < 90 && !flag_up) {
    flag_up = true;
  }
  for (uint8_t i=0; i<NUM_SWITCHES; i++) {
    if (swStatus[i] && swFlags[i]) {
      swFlags[i] = 0;
      handle_input(i);
      break;
    }
    else if (!swStatus[i] && !swFlags[i]) {
      swFlags[i] = 1;
    }
  }

  unsigned long current_millis = millis();
  if ((current_millis - previous_millis) > 40) {
    previous_millis = current_millis;
    handle_input(11);
  }
}
