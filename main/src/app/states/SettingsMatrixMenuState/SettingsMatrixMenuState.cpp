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

    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->columns; ++j) {
            matrix->setLed(0, i, j, true);
        }
    }
}

void SettingsMatrixMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsMatrixMenuState::cleanup() {
    joystick.clearHandlers();

    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->columns; ++j) {
            matrix->setLed(0, i, j, false);
        }
    }
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