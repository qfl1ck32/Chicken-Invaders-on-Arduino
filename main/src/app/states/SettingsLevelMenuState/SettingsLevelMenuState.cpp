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

    SettingsLevelMenuState::showNumberOnMatrix(game.level);
}

void SettingsLevelMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsLevelMenuState::cleanup() {
    joystick.clearHandlers();

    matrix->clear();
}

void SettingsLevelMenuState::goBack() {
    stateManager.changeState(settingsMenuStateId);
}

void SettingsLevelMenuState::increaseLevel() {
    game.changeLevel(game.level + 1);

    SettingsLevelMenuState::showNumberOnMatrix(game.level);
}

void SettingsLevelMenuState::decreaseLevel() {
    game.changeLevel(game.level - 1);

    SettingsLevelMenuState::showNumberOnMatrix(game.level);
}

void SettingsLevelMenuState::showNumberOnMatrix(byte number) {
    static const uint64_t matrixNumbers[] PROGMEM = {
        0x0010101014181000,
        0x00003c0810243800,
        0x00003c203c203c00,
        0x001010101c040400,
        0x00003c203c043c00,

    };

    uint64_t image;
    memcpy_P(&image, &matrixNumbers[number - 1], 8);

    matrix->displayImage(image);
}