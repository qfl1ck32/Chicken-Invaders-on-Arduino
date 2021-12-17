#include "./SettingsMatrixMenuState.h"

#include "../../globals.h"

void SettingsMatrixMenuState::setup() {
    static const char *const messages[] PROGMEM = {backMessage, increaseMessage, decreaseMessage};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {SettingsMatrixMenuState::goBack, SettingsMatrixMenuState::increaseIntensity, SettingsMatrixMenuState::decreaseIntensity};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    matrix->setAllLeds(true);
}

void SettingsMatrixMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsMatrixMenuState::cleanup() {
    joystick.clearHandlers();

    matrix->setAllLeds(false);
}

void SettingsMatrixMenuState::goBack() {
    stateManager.changeState(settingsMenuStateId);
}

void SettingsMatrixMenuState::increaseIntensity() {
    matrix->increaseIntensity(2);
}

void SettingsMatrixMenuState::decreaseIntensity() {
    matrix->increaseIntensity(-2);
}