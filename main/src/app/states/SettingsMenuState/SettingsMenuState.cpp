#include "./SettingsMenuState.h"

#include "../../globals.h"

void SettingsMenuState::setup() {
    static const char level[] PROGMEM = "Level";
    static const char lcd[] PROGMEM = "LCD";
    static const char matrixStr[] PROGMEM = "Matrix";
    static const char sounds[] PROGMEM = "Sounds";

    static const char *const messages[] PROGMEM = {backMessage, level, lcd, matrixStr, sounds};
    static byte numberOfMessages = sizeof(messages) / sizeof(char *);

    static const uint64_t hammerImage PROGMEM = 0x0345aa5428140a04;

    char **msgs = readArrayOfStringsFromPROGMEM(messages, numberOfMessages);

    menu.setMessages(msgs, numberOfMessages);

    HandlerFunction handlers[] = {goToMainMenu, SettingsMenuState::goToLevel, SettingsMenuState::goToLCD,
                                  SettingsMenuState::goToMatrix, SettingsMenuState::goToSounds};

    menu.setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    uint64_t image = readImageFromPROGMEM(&hammerImage);

    matrix->displayImage(image);
}

void SettingsMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsMenuState::cleanup() {
    joystick.clearHandlers();

    matrix->setAllLeds(false);
}

void SettingsMenuState::goToLevel() {
    stateManager.changeState<SettingsLevelMenuState>();
}

void SettingsMenuState::goToLCD() {
    stateManager.changeState<SettingsLCDMenuState>();
}

void SettingsMenuState::goToMatrix() {
    stateManager.changeState<SettingsMatrixMenuState>();
}

void SettingsMenuState::goToSounds() {
    stateManager.changeState<SettingsSoundsMenuState>();
}