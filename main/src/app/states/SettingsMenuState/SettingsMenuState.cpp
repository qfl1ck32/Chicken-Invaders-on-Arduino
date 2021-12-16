#include "./SettingsMenuState.h"

#include "../../globals.h"

void SettingsMenuState::setup() {
    static const char level[] PROGMEM = "Level";
    static const char lcd[] PROGMEM = "LCD";
    static const char matrixStr[] PROGMEM = "Matrix";
    static const char sounds[] PROGMEM = "Sounds";

    static const char *const messages[] PROGMEM = {backMessage, level, lcd, matrixStr, sounds};

    static const uint64_t hammerImage PROGMEM = 0x0345aa5428140a04;

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {SettingsMenuState::goBack, SettingsMenuState::goToLevel, SettingsMenuState::goToLCD,
                                  SettingsMenuState::goToMatrix, SettingsMenuState::goToSounds};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

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

    matrix->clear();
}

void SettingsMenuState::goBack() {
    stateManager.changeState(mainMenuStateId);
}

void SettingsMenuState::goToLevel() {
    stateManager.changeState(settingsLevelMenuStateId);
}

void SettingsMenuState::goToLCD() {
    stateManager.changeState(settingsLCDMenuStateId);
}

void SettingsMenuState::goToMatrix() {
    stateManager.changeState(settingsMatrixMenuStateId);
}

void SettingsMenuState::goToSounds() {
    stateManager.changeState(settingsSoundsMenuStateId);
}