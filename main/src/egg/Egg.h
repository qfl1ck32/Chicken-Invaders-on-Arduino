#ifndef Egg_h
#define Egg_h

#include "../constants/app.h"
#include "../delayer/Delayer.h"
#include "../unit/Unit.h"

class Egg : public Unit {
   public:
    Delayer delayer;

    Egg(int8_t, int8_t);

    void action();
    void behaviour(int8_t);

    unsigned char getType();
};

#endif
