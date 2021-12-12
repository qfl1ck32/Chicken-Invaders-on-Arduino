#pragma once

#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class Spaceship : public Unit {
   public:
    short lifes;

    Spaceship(short x, short y) : Unit(x, y) {
        this->lifes = 3;
    }

    static Pixel* contour;

    static void setup() {
        Spaceship::contour[0] = Pixel(0, -1);
        Spaceship::contour[1] = Pixel(0, 1);
        Spaceship::contour[2] = Pixel(-1, 0);
        Spaceship::contour[3] = Pixel(0, 0);
    }

    void action();
    void attack();

    void behaviour(short);

    void move(short, short);

    unsigned char getType();
};

Pixel* Spaceship::contour = new Pixel[4];
