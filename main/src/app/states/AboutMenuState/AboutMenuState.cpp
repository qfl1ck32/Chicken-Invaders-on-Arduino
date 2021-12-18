#include "./AboutMenuState.h"

#include "../../globals.h"

void AboutMenuState::setup() {
    static const char appName[] PROGMEM = "App Name: Invaders";
    static const char programmer[] PROGMEM = "Programmer: Rusu Andrei-Cristian";
    static const char github[] PROGMEM = "Github: https://github.com/qfl1ck32/Invaders-on-Arduino";

    static const char* const messages[] PROGMEM = {backMessage, appName, programmer, github};
    static byte numberOfMessages = sizeof(messages) / sizeof(char*);

    static const uint64_t icon PROGMEM = 0x0800081820202418;

    char** msgs = readArrayOfStringsFromPROGMEM(messages, numberOfMessages);

    menu.setMessages(msgs, numberOfMessages);

    HandlerFunction handlers[] = {goToMainMenu};
    menu.setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

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

    matrix->setAllLeds(false);
}
