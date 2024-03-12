#ifndef SNAKE_1_h
#define SNAKE_1_h

#include "animation.h"

class animSnake1 : public Animation {
    public:
        using Animation::Animation;
        void start() override;
        bool update() override;
    private:
        int limit = 15;
        int counter = 0;
        int direction = 0;
};

#endif
