#include "./Egg.h"

Egg ::Egg(int8_t x, int8_t y) : Unit(x, y) {
    this->delayer.updateInterval(200);
}

void Egg::action() {
    if (!this->delayer.canRun()) return;

    if (this->engine->unitMatrix[this->x + 1][this->y] != 0 && this->engine->unitMatrix[this->x + 1][this->y]->getType() == SPACESHIP_TYPE) {
        this->sendMessage(KILL, *this->engine->unitMatrix[this->x + 1][this->y]);
        this->die();
        return;
    }

    if (this->x == this->engine->rows - 2) {
        this->die();
        return;
    }

    this->move(1, 0);
};

void Egg::behaviour(int8_t action) {
    switch (action) {
        case KILL:
            this->die();
            break;
    }
};

unsigned char Egg::getType() {
    return EGG_TYPE;
}