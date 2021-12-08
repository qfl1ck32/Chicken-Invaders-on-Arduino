#pragma once

#include "../delayer/Delayer.h"
#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class Bullet : public Unit {
   public:
    Bullet(short x, short y) : Unit(x, y) {}

    Delayer delayer = Delayer(250);

    Bullet() {}

    void action() {
        if (!this->delayer.canRun()) return;

        if (this->engine->unitMatrix[this->x - 1][this->y] != 0 && this->engine->unitMatrix[this->x - 1][this->y]->getType() == CHICKEN_TYPE) {
            this->sendMessage(KILL, *this->engine->unitMatrix[this->x - 1][this->y]);
            this->die();
            return;
        }

        if (this->x == 1) {
            this->die();
            return;
        }

        this->move(-1, 0);
    };

    void behaviour(short action){

    };

    unsigned char getType() {
        return BULLET_TYPE;
    }
};
