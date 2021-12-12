#pragma once

#include "../delayer/Delayer.h"
#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class Chicken : public Unit {
   public:
    Delayer eggDelayer = Delayer(3000);

    Chicken(short x, short y) : Unit(x, y) {}

    Chicken() {}

    void action();
    void behaviour(short);
    unsigned char getType();

    static Pixel* contour;

    static void setup() {
        Chicken::contour[0] = Pixel(0, -1);
        Chicken::contour[1] = Pixel(0, 1);
        Chicken::contour[2] = Pixel(1, 0);
        Chicken::contour[3] = Pixel(0, 0);
    }

    static short getNumberOfChickensAlive();
};

Pixel* Chicken::contour = new Pixel[4];
