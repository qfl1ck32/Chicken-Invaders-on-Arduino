#pragma once

#include "../../utils/utils.h"

class GameOverState : public State {
   public:
    Delayer *delayer;

    GameOverState(int state) : State(state) {
        this->delayer = new Delayer(500);
    }

    void setup() {
        lcd->clear();

        // TODO: add logic to first show the person another screen
        // if he has the highest score
        button->setOnStateChange(GameOverState::goToMainMenu);
    }

    void handle() {
        // TODO: modularization
        int numberOfDigitsInScore = getNumberOfDigits(gameEngine->score);

        char gameOverMessage[20 + numberOfDigitsInScore];

        sprintf(gameOverMessage, "Game over. Score: %d.", gameEngine->score);

        lcd->printOnRow(gameOverMessage, 0);
        lcd->printOnRow(F("Press X to continue."), 1);

        if (this->delayer->canRun()) {
            lcd->scrollRow(0);
            lcd->scrollRow(1);
        }

        joystick->handleJoystickMovements();
    }

    void cleanup() {
        lcd->clear();
        button->clearHandler();
    }

    static void goToMainMenu() {
        stateManager->changeState(mainMenuStateId);
    }
};
