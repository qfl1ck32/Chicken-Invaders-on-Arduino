#pragma once

#include "./YouWonState.h"

#include "../../../utils/utils.cpp"
#include "../PlayingState/PlayingState.cpp"

void YouWonState::setup() {
    lcd->clear();
    joystick->clearHandlers();
    button->setOnStateChange(YouWonState::goToNextLevel);

    // TODO: not here
    matrix->clear();
}

void YouWonState::handle() {
    // TODO: modularization
    // FIXME: hmm
    // short numberOfDigitsInLevel = getNumberOfDigits(playingState->level);

    // char message[16 + numberOfDigitsInLevel];

    // sprintf(message, "You won level %d!", playingState->level);

    const char *message = "You won!";

    const char *pressXToContinue PROGMEM = "Press X to continue.";

    lcd->printOnRow(message, 0);
    lcd->printOnRow(pressXToContinue, 1);

    if (this->delayer.canRun()) {
        lcd->scrollRow(0);
        lcd->scrollRow(1);
    }
}

void YouWonState::cleanup() {
    button->clearHandler();
}

void YouWonState::goToNextLevel() {
    PlayingState::game->goToNextLevel();

    stateManager->changeState<PlayingState>();

    gameEngine->resetState();
}