#include "./Chicken.h"

#include "../app/states/YouWonState/YouWonState.cpp"
#include "../egg/Egg.cpp"

void Chicken::action() {
    if (this->eggDelayer.canRun()) {
        new Egg(this->x + 1, this->y);
    }
};

void Chicken::behaviour(short action) {
    switch (action) {
        case KILL:
            this->engine->score += 5;

            this->die();

            // TODO: static "count" on the class, + on new, - on delete
            short numberOfChickensAlive = Chicken::getNumberOfChickensAlive();

            if (numberOfChickensAlive == 0) {
                stateManager->changeState<YouWonState>();
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