#ifndef Egg_h
#define Egg_h

#include "../constants/app.h"
#include "../delayer/Delayer.h"
#include "../unit/Unit.h"

class Egg : public Unit {
   public:
    Delayer delayer = Delayer(500);

    Egg(byte x, byte y) : Unit(x, y) {}

    void action();
    void behaviour(byte);

    unsigned char getType();
};

#endif