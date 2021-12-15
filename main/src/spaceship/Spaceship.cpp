#include "./Spaceship.h"

#include "../app/globals.h"

void Spaceship::action(){

};

void Spaceship::attack() {
    // TODO: dry
    if (this->x - 1 < 0) return;

    if (this->engine.unitMatrix[this->x - 1][this->y] != 0) {
        if (this->engine.unitMatrix[this->x - 1][this->y]->getType() == CHICKEN_TYPE) {
            this->sendMessage(KILL, *this->engine.unitMatrix[this->x - 1][this->y]);
        }

        return;
    }

    new Bullet(this->x - 2, this->y);
}

void Spaceship::behaviour(byte action) {
    switch (action) {
        case KILL:
            --this->lifes;

            if (this->lifes == 0) {
                stateManager.changeState(gameOverStateId);
            }

            return;
    }
};

void Spaceship::move(byte dx, byte dy) {
    if (!this->isValidPosition(this->x + dx, this->y + dy)) return;

    Unit *unit = this->engine.unitMatrix[this->x + dx][this->y + dy];

    // TODO: DRY
    if (unit &&
        (unit->getType() == EGG_TYPE || unit->getType() == CHICKEN_TYPE)) {
        // we don't wanna hurt chickens
        if (unit->getType() == EGG_TYPE) {
            this->sendMessage(KILL, *unit);
        }

        this->sendMessage(KILL, *this->engine.unitMatrix[this->x][this->y]);
        return;
    }

    Unit::move(dx, dy);
}

unsigned char Spaceship::getType() {
    return SPACESHIP_TYPE;
}