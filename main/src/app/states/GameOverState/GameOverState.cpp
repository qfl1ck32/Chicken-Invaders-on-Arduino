#include "./GameOverState.h"

#include "../../globals.h"

void GameOverState::setup() {
    lcd->clear();

    // TODO: add logic to first show the person another screen
    // if he has the highest score
    button.setOnStateChange(GameOverState::goToNextStep);

    // TODO: not here
    matrix->clear();

    game.needsInitialisation = true;
}

void GameOverState::handle() {
    // TODO: modularization
    int numberOfDigitsInScore = getNumberOfDigits(game.score);

    char gameOverMessage[20 + numberOfDigitsInScore];

    const char* const gameOverMsg = "Game over. Score:";
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
    // TODO: please do something, lol
    if (game.score + 5 > leaderboard.getHighscore()) {
        // TODO: add logic
        // leaderboard.write(nameSelector->name, game.score + 5);
        stateManager.changeState(nameSelectionStateId);
        ;
    }

    else {
        stateManager.changeState(mainMenuStateId);
        ;
    }

    // FIXME
    // gameEngine.resetState();
}