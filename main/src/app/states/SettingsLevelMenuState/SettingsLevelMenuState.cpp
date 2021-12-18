#include "./SettingsLevelMenuState.h"

#include "../../globals.h"

// TODO: show the level on the matrix
void SettingsLevelMenuState::setup() {
    static const char *const messages[] PROGMEM = {backMessage, increaseMessage, decreaseMessage};
    static byte numberOfMessages = sizeof(messages) / sizeof(char *);

    char **msgs = readArrayOfStringsFromPROGMEM(messages, numberOfMessages);

    menu.setMessages(msgs, numberOfMessages);

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
    setSettingsLevel(settingsLevel + 1);

    SettingsLevelMenuState::showLevel();
}

void SettingsLevelMenuState::decreaseLevel() {
    setSettingsLevel(settingsLevel - 1);

    SettingsLevelMenuState::showLevel();
}

void SettingsLevelMenuState::showLevel() {
    uint64_t image = readImageFromPROGMEM(&matrixNumbers[settingsLevel - 1]);

    matrix->displayImage(image);
}
