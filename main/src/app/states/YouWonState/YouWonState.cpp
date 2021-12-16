#include "./YouWonState.h"

#include "../../globals.h"

void YouWonState::setup() {
    // FIXME: progmem :)

    // static const char youWonLevelMessage[] PROGMEM = "You won level ";

    // short numberOfDigitsInLevel = getNumberOfDigits(game.level);

    // char pressXToContinue[21];
    // char youWonLevel[15];

    // // FIXME what's going on? reading just one of them works.
    // readFromPROGMEM(pressXToContinueMessage, pressXToContinue, 20);
    // readFromPROGMEM(youWonLevelMessage, youWonLevel, 14);

    // char youWon[15 + numberOfDigitsInLevel];

    // sprintf(youWon, "%s%d!", youWonLevel, game.level);

    short numberOfDigitsInLevel = getNumberOfDigits(game.level);

    char youWon[16 + numberOfDigitsInLevel];

    sprintf(youWon, "You won level %d!", game.level);

    const char* const pressXToContinue = "Press X to continue.";

    lcd->printOnRow(youWon, 0);
    lcd->printOnRow(pressXToContinue, 1);

    lcd->printOnRow(youWon, 0);
    lcd->printOnRow(pressXToContinue, 1);

    lcd->clear();
    joystick.clearHandlers();

    button.setOnStateChange(YouWonState::goToNextLevel);

    matrix->clear();

    // TODO: add logic for finishing last level!
    matrix->displayImage(matrixNumbers[game.level + 1]);
}

void YouWonState::handle() {
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
}