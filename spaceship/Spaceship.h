#pragma once

#include "../bullet/Bullet.h"
#include "../pixel/Pixel.h"
#include "../unit/Unit.cpp"
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

    void action(){

    };

    void attack() {
        new Bullet(this->x - 2, this->y);
    }

    void behaviour(short action) {
        switch (action) {
            case KILL:
                --this->lifes;

                if (this->lifes == 0) {
                    stateManager->changeState(gameOverStateId);
                }

                return;
        }
    };

    unsigned char getType() {
        return SPACESHIP_TYPE;
    }
};

Pixel* Spaceship::contour = new Pixel[4];
