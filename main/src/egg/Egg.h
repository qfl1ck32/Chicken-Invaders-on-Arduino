#ifndef Egg_h
#define Egg_h

#include "../constants/app.h"
#include "../delayer/Delayer.h"
#include "../unit/Unit.h"

class Egg : public Unit {
   public:
    Delayer delayer = Delayer(500);

    Egg(int8_t x, int8_t y) : Unit(x, y) {}

    void action();
    void behaviour(int8_t);

    unsigned char getType();
};

#endif
