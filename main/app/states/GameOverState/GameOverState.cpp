#pragma once

#include "./GameOverState.h"

#include "../../../utils/utils.cpp"
#include "../MainMenuState/MainMenuState.cpp"
#include "../NameSelectionState/NameSelectionState.cpp"
#include "../PlayingState/PlayingState.cpp"

class MainMenuState;

void GameOverState::setup() {
    lcd->clear();

    // TODO: add logic to first show the person another screen
    // if he has the highest score
    button->setOnStateChange(GameOverState::goToNextStep);

    // TODO: not here
    matrix->clear();

    PlayingState::game->needsInitialisation = true;
}

void GameOverState::handle() {
    // TODO: modularization
    int numberOfDigitsInScore = getNumberOfDigits(PlayingState::game->score);

    char gameOverMessage[20 + numberOfDigitsInScore];

    const char* const gameOverMsg PROGMEM = "Game over. Score:";

    sprintf(gameOverMessage, "%s: %d.", gameOverMsg, PlayingState::game->score);

    lcd->printOnRow(gameOverMessage, 0);
    lcd->printOnRow(pressXToContinue, 1);

    if (this->delayer.canRun()) {
        lcd->scrollRow(0);
        lcd->scrollRow(1);
    }

    joystick->handleJoystickMovements();
}

void GameOverState::cleanup() {
    lcd->clear();
    button->clearHandler();
}

void GameOverState::goToNextStep() {
    // TODO: please do something, lol
    if (PlayingState::game->score + 5 > leaderboard->getHighscore()) {
        // TODO: add logic
        // leaderboard->write(nameSelector->name, PlayingState::game->score + 5);
        stateManager->changeState<NameSelectionState>();
    }

    else {
        stateManager->changeState<MainMenuState>();
    }

    gameEngine->resetState();
}