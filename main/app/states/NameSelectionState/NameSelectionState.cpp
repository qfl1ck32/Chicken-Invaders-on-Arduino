#pragma once

#include "./NameSelectionState.h"

void NameSelectionState::handle() {
    joystick->handleJoystickMovementOnAxisX();
    joystick->handleJoystickMovementOnAxisY();

    nameSelector->main();
}

void NameSelectionState::setup() {
    joystick->setHandlerOnXAxisChangeLeft(NameSelectionState::goLeft);
    joystick->setHandlerOnXAxisChangeRight(NameSelectionState::goRight);
    joystick->setHandlerOnYAxisChangeUp(NameSelectionState::goUp);
    joystick->setHandlerOnYAxisChangeDown(NameSelectionState::goDown);
    joystick->setHandlerSwStateChange(NameSelectionState::handleSwStateChange);

    button->setOnStateChange(NameSelectionState::finish);
}

void NameSelectionState::cleanup() {
    joystick->clearHandlers();

    button->clearHandler();

    lcd->clear();
    lcd->noBlink();
}

void NameSelectionState::goUp() {
    nameSelector->goUp();
}

void NameSelectionState::goDown() {
    nameSelector->goDown();
}

void NameSelectionState::goLeft() {
    nameSelector->goLeft();
}

void NameSelectionState::goRight() {
    nameSelector->goRight();
}

void NameSelectionState::handleSwStateChange() {
    nameSelector->select();
}

void NameSelectionState::finish() {
    if (nameSelector->finish()) {
        // TODO: update logic
        leaderboard->write(nameSelector->name, gameEngine->score);
        stateManager->changeState<MainMenuState>();
    }
}