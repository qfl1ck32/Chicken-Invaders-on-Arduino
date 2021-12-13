#pragma once

#include "./AboutMenuState.h"

#include "../MainMenuState/MainMenuState.cpp"

void AboutMenuState::setup() {
    const char *messages[] PROGMEM = {"Back", "App Name: Chicken Invaders", "Programmer: Rusu Andrei-Cristian",
                                      "Github: https://github.com/qfl1ck32/Chicken-Invaders-on-Arduino"};

    menu->setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {AboutMenuState::goBack};
    menu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick->clearHandlers();
    button->clearHandler();

    joystick->setHandlerOnYAxisChangeUp(menuGoUp);
    joystick->setHandlerOnYAxisChangeDown(menuGoDown);

    joystick->setHandlerSwStateChange(menuSelect);
}

void AboutMenuState::handle() {
    menu->run(true);
    joystick->handleJoystickMovements();
}

void AboutMenuState::cleanup() {
    joystick->clearHandlers();
    button->clearHandler();

    lcd->clear();
}

void AboutMenuState::goBack() {
    stateManager->changeState<MainMenuState>();
}