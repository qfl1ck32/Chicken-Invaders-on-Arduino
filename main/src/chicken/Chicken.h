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
    static byte count;

    Delayer eggDelayer = Delayer(2000);
    Delayer moveDelayer = Delayer(1250);

    Chicken(byte, byte);

    void action();
    void behaviour(byte);
    unsigned char getType();

    void die();
};

#endif
