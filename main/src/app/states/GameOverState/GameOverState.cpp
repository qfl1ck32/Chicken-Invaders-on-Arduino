#include "./GameOverState.h"

#include "../../globals.h"

void GameOverState::setup() {
    // TODO: progmem :)

    button.setOnStateChange(GameOverState::goToNextStep);

    game.reset();

    Unit::engine->resetState();

    int numberOfDigitsInScore = getNumberOfDigits(game.score);

    char gameOverMessage[21 + numberOfDigitsInScore];

    static const char *pressXToContinue = "Press X to continue.";

    sprintf(gameOverMessage, "Game over. Score: %d.", game.score);

    lcd->printOnRow(gameOverMessage, 0);
    lcd->printOnRow(pressXToContinue, 1);
}

void GameOverState::handle() {
    if (this->delayer.canRun()) {
        lcd->scrollRow(0);
        lcd->scrollRow(1);
    }

    joystick.handleJoystickMovements();
}

void GameOverState::cleanup() {
    lcd->clear();
    button.clearHandler();
}

void GameOverState::goToNextStep() {
    if (leaderboard.isHighScore(game.score)) {
        stateManager.changeState(nameSelectionStateId);
    } else {
        stateManager.changeState(mainMenuStateId);
    }
}
