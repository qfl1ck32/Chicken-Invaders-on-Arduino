#ifndef Chicken_h
#define Chicken_h

#include "../app/states/YouWonState/YouWonState.h"
#include "../constants/app.h"
#include "../delayer/Delayer.h"
#include "../egg/Egg.h"
#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class Chicken : public Unit {
   public:
    static int8_t count;

    Delayer eggDelayer = Delayer(CHICKEN_INITIAL_EGG_DELAYER_INTERVAL);
    Delayer moveDelayer = Delayer(CHICKEN_INITIAL_MOVE_DELAYER_INTERVAL);

    Chicken(int8_t, int8_t);

    void action();
    void behaviour(int8_t);
    unsigned char getType();

    void die();
};

#endif
