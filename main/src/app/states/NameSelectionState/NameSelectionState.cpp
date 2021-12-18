#include "./NameSelectionState.h"

#include "../../globals.h"

NameSelector* NameSelectionState::nameSelector = nullptr;
Leaderboard* NameSelectionState::leaderboard = nullptr;

NameSelectionState::NameSelectionState() {
    NameSelectionState::leaderboard = new Leaderboard();
    NameSelectionState::nameSelector = new NameSelector(lcd, 1);
}

// TODO: fix this. why is the last delete breaking the app?
NameSelectionState::~NameSelectionState() {
    delete NameSelectionState::leaderboard;
    // delete NameSelectionState::nameSelector;
}

void NameSelectionState::handle() {
    joystick.handleJoystickMovementOnAxisX();
    joystick.handleJoystickMovementOnAxisY();

    nameSelector->main();
}

void NameSelectionState::setup() {
    static const char msg[] PROGMEM = "Enter your name:";

    static const uint64_t icon PROGMEM = 0x00003c4200240000;

    joystick.setOnChangeLeft(NameSelectionState::goLeft);
    joystick.setOnChangeRight(NameSelectionState::goRight);
    joystick.setOnChangeUp(NameSelectionState::goUp);
    joystick.setOnChangeDown(NameSelectionState::goDown);
    joystick.setOnSwStateChange(NameSelectionState::handleSwStateChange);

    button.setOnStateChange(NameSelectionState::finish);

    char* message = readStringFromPROGMEM(msg);

    lcd->printOnRow(message, 0);

    delete message;

    uint64_t image = readImageFromPROGMEM(&icon);

    matrix->displayImage(image);
}

void NameSelectionState::cleanup() {
    joystick.clearHandlers();
    button.clearHandler();

    lcd->clear();
    lcd->noBlink();

    matrix->setAllLeds(false);
}

void NameSelectionState::goUp() {
    NameSelectionState::nameSelector->goUp();
}

void NameSelectionState::goDown() {
    NameSelectionState::nameSelector->goDown();
}

void NameSelectionState::goLeft() {
    NameSelectionState::nameSelector->goLeft();
}

void NameSelectionState::goRight() {
    NameSelectionState::nameSelector->goRight();
}

void NameSelectionState::handleSwStateChange() {
    NameSelectionState::nameSelector->select();
}

void NameSelectionState::finish() {
    if (NameSelectionState::nameSelector->finish()) {
        NameSelectionState::leaderboard->write(NameSelectionState::nameSelector->name, PlayingState::score);

        stateManager.changeState<MainMenuState>();
    }
}
