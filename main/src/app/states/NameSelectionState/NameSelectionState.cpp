#include "./NameSelectionState.h"

#include "../../globals.h"

void NameSelectionState::handle() {
    joystick.handleJoystickMovementOnAxisX();
    joystick.handleJoystickMovementOnAxisY();

    nameSelector->main();
}

void NameSelectionState::setup() {
    joystick.setOnChangeLeft(NameSelectionState::goLeft);
    joystick.setOnChangeRight(NameSelectionState::goRight);
    joystick.setOnChangeUp(NameSelectionState::goUp);
    joystick.setOnChangeDown(NameSelectionState::goDown);
    joystick.setOnSwStateChange(NameSelectionState::handleSwStateChange);

    button.setOnStateChange(NameSelectionState::finish);
}

void NameSelectionState::cleanup() {
    joystick.clearHandlers();

    button.clearHandler();

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
        leaderboard.write(nameSelector->name, game.score);
        stateManager.changeState(mainMenuStateId);
        }
}
