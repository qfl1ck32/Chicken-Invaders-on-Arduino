#pragma once

#include "../../utils/utils.h"
#include "../app.h"

class YouWonState : public State {
   public:
    Delayer delayer = Delayer(350);

    YouWonState(int state) : State(state) {}

    void setup() {
        lcd->clear();
        joystick->clearHandlers();
        button->setOnStateChange(YouWonState::goToNextLevel);

        // TODO: not here
        matrix->clear();
    }

    void handle() {
        // TODO: modularization
        short numberOfDigitsInLevel = getNumberOfDigits(playingState->level);

        char message[16 + numberOfDigitsInLevel];

        sprintf(message, "You won level %d!", playingState->level);

        lcd->printOnRow(message, 0);
        lcd->printOnRow(F("Press X to continue."), 1);

        if (this->delayer.canRun()) {
            lcd->scrollRow(0);
            lcd->scrollRow(1);
        }
    }

    void cleanup() {
        button->clearHandler();
    }

    static void goToNextLevel() {
        // TODO: rip modularization
        ++playingState->level;
        stateManager->changeState(playingStateId);
    }
};
