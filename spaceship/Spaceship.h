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
        // TODO: dry
        if (this->x - 1 < 0) return;

        if (this->engine->unitMatrix[this->x - 1][this->y] != 0) {
            if (this->engine->unitMatrix[this->x - 1][this->y]->getType() == CHICKEN_TYPE) {
                this->sendMessage(KILL, *this->engine->unitMatrix[this->x - 1][this->y]);
            }

            return;
        }

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

    void move(short dx, short dy) {
        if (!this->isValidPosition(this->x + dx, this->y + dy)) return;

        // TODO: DRY
        if (this->engine->unitMatrix[this->x + dx][this->y + dy] &&
            (this->engine->unitMatrix[this->x + dx][this->y + dy]->getType() == EGG_TYPE || this->engine->unitMatrix[this->x + dx][this->y + dy]->getType() == CHICKEN_TYPE)) {
            // we don't wanna hurt chickens
            if (this->engine->unitMatrix[this->x + dx][this->y + dy]->getType() == EGG_TYPE) {
                this->sendMessage(KILL, *this->engine->unitMatrix[this->x + dx][this->y + dy]);
            }

            this->sendMessage(KILL, *this->engine->unitMatrix[this->x][this->y]);
            return;
        }

        Unit::move(dx, dy);
    }

    unsigned char getType() {
        return SPACESHIP_TYPE;
    }
};

Pixel* Spaceship::contour = new Pixel[4];
