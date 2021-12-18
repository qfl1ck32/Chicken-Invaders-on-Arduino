#ifndef Chicken_h
#define Chicken_h

#include "../constants/app.h"
#include "../delayer/Delayer.h"
#include "../egg/Egg.h"
#include "../unit/Unit.h"

class Chicken : public Unit {
   public:
    static int8_t count;

    Delayer eggDelayer;
    Delayer moveDelayer;

    Chicken(int8_t, int8_t);

    void action();
    void behaviour(int8_t);
    unsigned char getType();

    void die();
};

#endif
