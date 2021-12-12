#pragma once

#include "../delayer/Delayer.h"
#include "../unit/Unit.h"

class Egg : public Unit {
   public:
    Delayer delayer = Delayer(500);

    Egg(short x, short y) : Unit(x, y) {}

    void action();
    void behaviour(short);

    unsigned char getType();
};
