#include "./Spaceship.h"

#include "../app/states/GameOverState/GameOverState.cpp"
#include "../bullet/Bullet.cpp"
#include "../unit/Unit.cpp"

void Spaceship::action(){

};

void Spaceship::attack() {
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

void Spaceship::behaviour(short action) {
    switch (action) {
        case KILL:
            --this->lifes;

            if (this->lifes == 0) {
                stateManager->changeState<GameOverState>();
            }

            return;
    }
};

void Spaceship::move(short dx, short dy) {
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

unsigned char Spaceship::getType() {
    return SPACESHIP_TYPE;
}