#pragma once

#include "../delayer/Delayer.h"
#include "../egg/Egg.h"
#include "../pixel/Pixel.h"
#include "../unit/Unit.h"

class Chicken : public Unit {
   public:
    Delayer eggDelayer = Delayer(1500);

    Chicken(short x, short y) : Unit(x, y) {}

    Chicken() {
    }

    static Pixel* contour;

    static void setup() {
        Chicken::contour[0] = Pixel(0, -1);
        Chicken::contour[1] = Pixel(0, 1);
        Chicken::contour[2] = Pixel(1, 0);
        Chicken::contour[3] = Pixel(0, 0);
    }

    void action() {
        if (this->eggDelayer.canRun()) {
            new Egg(this->x + 1, this->y);
        }
    };

    void behaviour(short action) {
        switch (action) {
            case KILL:
                this->engine->score += 5;

                this->die();

                // TODO: static "count" on the class, + on new, - on delete
                short numberOfChickensAlive = Chicken::getNumberOfChickensAlive();

                if (numberOfChickensAlive == 0) {
                    stateManager->changeState(youWonStateId);
                }

                return;
        }
    };

    unsigned char getType() {
        return CHICKEN_TYPE;
    }

    static short getNumberOfChickensAlive() {
        short answer = 0;

        for (int i = 0; i < Unit::engine->numberOfUnits; ++i) {
            if (Unit::engine->unitArray[i]->getType() == CHICKEN_TYPE && Unit::engine->unitArray[i]->isAlive) answer += 1;
        }

        return answer;
    }
};

Pixel* Chicken::contour = new Pixel[4];
