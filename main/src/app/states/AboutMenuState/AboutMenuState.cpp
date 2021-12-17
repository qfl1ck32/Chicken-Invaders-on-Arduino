#include "./AboutMenuState.h"

#include "../../globals.h"

void AboutMenuState::setup() {
    // static const char appName[] PROGMEM = "App Name: Invaders";
    // static const char programmer[] PROGMEM = "Programmer: Rusu Andrei-Cristian";
    // static const char github[] PROGMEM = "Github: https://github.com/qfl1ck32/Invaders-on-Arduino";

    static const char* const messages[] PROGMEM = {backMessage};

    static const uint64_t icon PROGMEM = 0x0800081820202418;

    // menu.setMessages(messages, sizeof(messages) / sizeof(char*));

    HandlerFunction handlers[] = {AboutMenuState::goBack};
    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.clearHandlers();
    button.clearHandler();

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    uint64_t image = readImageFromPROGMEM(&icon);

    matrix->displayImage(image);
}

void AboutMenuState::handle() {
    menu.run(true);
    joystick.handleJoystickMovements();
}

void AboutMenuState::cleanup() {
    joystick.clearHandlers();
    button.clearHandler();

    lcd->clear();

    matrix->clear();
}

void AboutMenuState::goBack() {
    stateManager.changeState(mainMenuStateId);
    ;
}
