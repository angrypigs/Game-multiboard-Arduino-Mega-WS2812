#include "stack.h"

Stack& Stack::operator=(const Stack& other) {
    if (this != &other) {
        for (int i = 0; i < 4; i++) {
            this->table[i] = other.table[i];
        }
        this->top = other.top;
    }
    return *this;
}

void Stack::push(uint8_t val) {
    if (top < SIZE) {
        table[top] = val;
        top++;
    }
}

uint8_t Stack::pop() {
    if (top > 0) {
        top--;
    }
    uint8_t val = table[top];
    table[top] = 0;
    return val;
}

uint8_t Stack::top_element() {
    if (top > 0) {
        return table[top - 1];
    }
    return 0;
}
