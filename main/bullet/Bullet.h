#pragma once

#include "../delayer/Delayer.h"
#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class Bullet : public Unit {
   public:
    Bullet(short x, short y) : Unit(x, y) {}

    Delayer delayer = Delayer(250);

    Bullet() {}

    void action();

    void behaviour(short);

    unsigned char getType();
};
