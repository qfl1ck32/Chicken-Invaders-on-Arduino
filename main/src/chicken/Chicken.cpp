#include "./Chicken.h"

#include "../app/globals.h"

int8_t Chicken::count = 0;

Chicken::Chicken(int8_t x, int8_t y) : Unit(x, y) {
    ++Chicken::count;

    this->eggDelayer.updateInterval(CHICKEN_INITIAL_EGG_DELAYER_INTERVAL);
    this->moveDelayer.updateInterval(CHICKEN_INITIAL_MOVE_DELAYER_INTERVAL);
}

void Chicken::action() {
    if (this->eggDelayer.canRun()) {
        new Egg(this->x + 1, this->y);
    }

    short rand = random(3);

    if (rand == 0) return;

    short direction = rand == 1 ? -1 : 1;

    if (this->moveDelayer.canRun()) {
        if (!this->engine->isValidPosition(this->x, this->y + direction) || this->engine->unitMatrix[this->x][this->y + direction] != 0) {
            return;
        }

        this->move(0, direction);
    }
};

void Chicken::die() {
    Unit::die();

    --Chicken::count;
}

void Chicken::behaviour(int8_t action) {
    switch (action) {
        case KILL:
            this->die();

            return;
    }
};

unsigned char Chicken::getType() {
    return CHICKEN_TYPE;
}
