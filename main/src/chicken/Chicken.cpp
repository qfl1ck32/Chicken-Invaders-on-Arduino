#include "./Chicken.h"

#include "../app/globals.h"

int8_t Chicken::count = 0;

Chicken::Chicken(int8_t x, int8_t y) : Unit(x, y) {
    ++Chicken::count;
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
            // TODO: it would be very nice to have an event manager.
            game.score += 5;

            this->die();

            if (Chicken::count == 0) {
                stateManager.changeState(youWonStateId);
            }

            return;
    }
};

unsigned char Chicken::getType() {
    return CHICKEN_TYPE;
}
