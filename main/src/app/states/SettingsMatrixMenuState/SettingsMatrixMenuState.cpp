#include "./SettingsMatrixMenuState.h"

#include "../../globals.h"

void SettingsMatrixMenuState::setup() {
    static const char *const messages[] PROGMEM = {backMessage, increaseMessage, decreaseMessage};
    static byte numberOfMessages = sizeof(messages) / sizeof(char *);

    char **msgs = readArrayOfStringsFromPROGMEM(messages, numberOfMessages);

    menu.setMessages(msgs, numberOfMessages);

    HandlerFunction handlers[] = {goToSettingsMenu, SettingsMatrixMenuState::increaseIntensity, SettingsMatrixMenuState::decreaseIntensity};

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

void SettingsMatrixMenuState::increaseIntensity() {
    matrix->increaseIntensity(2);
}

void SettingsMatrixMenuState::decreaseIntensity() {
    matrix->increaseIntensity(-2);
}