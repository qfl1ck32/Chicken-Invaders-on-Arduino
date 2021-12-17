#include "./SettingsLevelMenuState.h"

#include "../../globals.h"

// TODO: show the level on the matrix
void SettingsLevelMenuState::setup() {
    static const char *const messages[] PROGMEM = {backMessage, increaseMessage, decreaseMessage};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {SettingsLevelMenuState::goBack, SettingsLevelMenuState::increaseLevel, SettingsLevelMenuState::decreaseLevel};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    SettingsLevelMenuState::showLevel();
}

void SettingsLevelMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsLevelMenuState::cleanup() {
    joystick.clearHandlers();

    matrix->setAllLeds(false);
}

void SettingsLevelMenuState::goBack() {
    stateManager.changeState<SettingsMenuState>();
}

void SettingsLevelMenuState::increaseLevel() {
    setLevel(level + 1);

    SettingsLevelMenuState::showLevel();
}

void SettingsLevelMenuState::decreaseLevel() {
    setLevel(level - 1);

    SettingsLevelMenuState::showLevel();
}

void SettingsLevelMenuState::showLevel() {
    uint64_t image = readImageFromPROGMEM(&matrixNumbers[level - 1]);

    matrix->displayImage(image);
}
