#include "./YouWonState.h"

#include "../../globals.h"

void YouWonState::setup() {
    lcd->clear();
    joystick.clearHandlers();
    button.setOnStateChange(YouWonState::goToNextLevel);

    // TODO: not here
    matrix->clear();
}

void YouWonState::handle() {
    // TODO: modularization
    // FIXME: hmm
    // short numberOfDigitsInLevel = getNumberOfDigits(playingState->level);

    // char message[16 + numberOfDigitsInLevel];

    // sprintf(message, "You won level %d!", playingState->level);

    const char* const youWon = "You won!";
    const char* const pressXToContinue = "Press X to continue.";

    lcd->printOnRow(youWon, 0);
    lcd->printOnRow(pressXToContinue, 1);

    if (this->delayer.canRun()) {
        lcd->scrollRow(0);
        lcd->scrollRow(1);
    }
}

void YouWonState::cleanup() {
    button.clearHandler();
}

void YouWonState::goToNextLevel() {
    game.goToNextLevel();

    stateManager.changeState<PlayingState>();

    // gameEngine.resetState();
}