#include "./GameOverState.h"

#include "../../globals.h"

void GameOverState::setup() {
    lcd->clear();

    // TODO: add logic to first show the person another screen
    // if he has the highest score
    button.setOnStateChange(GameOverState::goToNextStep);

    // TODO: not here
    matrix->clear();

    game.reset();
    gameEngine->resetState();
}

void GameOverState::handle() {
    // TODO: modularization
    int numberOfDigitsInScore = getNumberOfDigits(game.score);

    char gameOverMessage[21 + numberOfDigitsInScore];

    const char* const gameOverMsg = "Game over. Score: ";
    const char* const pressXToContinue = "Press X to continue.";

    sprintf(gameOverMessage, "%s: %d.", gameOverMsg, game.score);

    lcd->printOnRow(gameOverMessage, 0);
    lcd->printOnRow(pressXToContinue, 1);

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
