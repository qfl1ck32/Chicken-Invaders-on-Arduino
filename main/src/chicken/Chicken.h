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
    Delayer eggDelayer = Delayer(2000);
    Delayer moveDelayer = Delayer(1250);

    Chicken(byte x, byte y) : Unit(x, y) {}

    Chicken() {}

    void action();
    void behaviour(byte);
    unsigned char getType();

    static short getNumberOfChickensAlive();
};

#endif
