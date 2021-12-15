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
    short numberOfDigitsInLevel = getNumberOfDigits(game.level);

    char youWon[16 + numberOfDigitsInLevel];

    sprintf(youWon, "You won level %d!", game.level);

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

    stateManager.changeState(playingStateId);

    gameEngine->resetState();
}