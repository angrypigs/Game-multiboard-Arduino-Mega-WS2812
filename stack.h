#ifndef stack_h
#define stack_h

#include "Arduino.h"

class Stack {
  public:
    Stack& operator=(const Stack &other);
    const uint8_t SIZE = 4;
    uint8_t table[4] = {0, 0, 0, 0};
    uint8_t top = 0;
    void push(uint8_t val);
    uint8_t pop();
    uint8_t top_element();
};

#endif