#ifndef ANIM_SNAKE_1_h
#define ANIM_SNAKE_1_h

#include "animation.h"

class animSnake1 : public Animation {
    public:
        void start();
        bool update();
    private:
        int limit = 15;
        int counter = 0;
        int direction = 0;
};

#endif