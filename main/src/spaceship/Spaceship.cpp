#include "./Spaceship.h"

#include "../app/globals.h"

Spaceship::Spaceship(int8_t x, int8_t y) : Unit(x, y) {
    this->lifes = 3;
}

void Spaceship::action(){

};

void Spaceship::attack() {
    if (this->x - 1 < 0) return;

    Unit *unit = this->engine->unitMatrix[this->x - 1][this->y];

    if (unit != 0) {
        if (unit->getType() == CHICKEN_TYPE) {
            this->sendMessage(KILL, *unit);
        }

        return;
    }

    new Bullet(this->x - 2, this->y);
}

void Spaceship::behaviour(int8_t action) {
    switch (action) {
        case KILL:
            --this->lifes;
            return;
    }
};

void Spaceship::move(short dx, short dy) {
    if (!this->isValidPosition(this->x + dx, this->y + dy)) return;

    Unit *unitOnSpot = this->engine->unitMatrix[this->x + dx][this->y + dy];

    if (unitOnSpot != 0) {
        unsigned char type = unitOnSpot->getType();

        if (type == CHICKEN_TYPE || type == EGG_TYPE) {
            if (type == EGG_TYPE) {
                this->sendMessage(KILL, *this->engine->unitMatrix[this->x + dx][this->y + dy]);
            }

            this->sendMessage(KILL, *this->engine->unitMatrix[this->x][this->y]);
            return;
        }
    }

    Unit::move(dx, dy);
}

unsigned char Spaceship::getType() {
    return SPACESHIP_TYPE;
}
