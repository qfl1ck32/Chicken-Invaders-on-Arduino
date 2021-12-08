#pragma once

#include "../delayer/Delayer.h"
#include "../unit/Unit.h"

class Egg : public Unit {
   public:
    Delayer delayer = Delayer(500);

    Egg(short x, short y) : Unit(x, y) {}

    void action() {
        if (!this->delayer.canRun()) return;

        if (this->engine->unitMatrix[this->x + 1][this->y] != 0 && this->engine->unitMatrix[this->x + 1][this->y]->getType() == SPACESHIP_TYPE) {
            this->sendMessage(KILL, *this->engine->unitMatrix[this->x + 1][this->y]);
            this->die();
            return;
        }

        if (this->x == this->engine->matrix->rows - 2) {
            this->die();
            return;
        }

        this->move(1, 0);
    };

    void behaviour(short action){

    };

    unsigned char getType() {
        return EGG_TYPE;
    }
};
