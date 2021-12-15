#include "./Chicken.h"

#include "../app/globals.h"

void Chicken::action() {
    if (this->eggDelayer.canRun()) {
        new Egg(this->x + 1, this->y);
    }

    short rand = random(2);

    short direction = rand == 0 ? -1 : 1;

    return;

    if (this->moveDelayer.canRun()) {
        if (!this->engine->isValidPosition(this->x, this->y + direction) || this->engine->unitMatrix[this->x][this->y + direction] != 0) {
            return;
        }

        this->move(0, direction);
    }
};

void Chicken::behaviour(byte action) {
    switch (action) {
        case KILL:
            game.score += 5;

            this->die();

            // TODO: static "count" on the class, + on new, - on delete
            short numberOfChickensAlive = Chicken::getNumberOfChickensAlive();

            if (numberOfChickensAlive == 0) {
                stateManager.changeState(youWonStateId);
            }

            return;
    }
};

unsigned char Chicken::getType() {
    return CHICKEN_TYPE;
}

short Chicken::getNumberOfChickensAlive() {
    short answer = 0;

    for (int i = 0; i < Unit::engine->numberOfUnits; ++i) {
        if (Unit::engine->unitArray[i]->getType() == CHICKEN_TYPE && Unit::engine->unitArray[i]->isAlive) answer += 1;
    }

    return answer;
}