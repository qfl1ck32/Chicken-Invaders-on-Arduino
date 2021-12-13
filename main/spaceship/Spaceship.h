#pragma once

#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class Spaceship : public Unit {
   public:
    short lifes;

    Spaceship(byte x, byte y) : Unit(x, y) {
        this->lifes = 3;
    }

    void action();
    void attack();

    void behaviour(byte);

    void move(byte, byte);

    unsigned char getType();
};
