#pragma once

#include "./SettingsMenuState.h"

#include "../MainMenuState/MainMenuState.cpp"
#include "../SettingsLCDMenuState/SettingsLCDMenuState.cpp"
#include "../SettingsMatrixMenuState/SettingsMatrixMenuState.cpp"

void SettingsMenuState::setup() {
    static const char *const messages[] PROGMEM = {"Back", "Lvl", "LCD", "Matrix"};

    menu->setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {SettingsMenuState::goBack, SettingsMenuState::goToLevel, SettingsMenuState::goToLCD,
                                  SettingsMenuState::goToMatrix};

    menu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick->setHandlerOnYAxisChangeUp(menuGoUp);
    joystick->setHandlerOnYAxisChangeDown(menuGoDown);

    joystick->setHandlerSwStateChange(menuSelect);
}

void SettingsMenuState::handle() {
    menu->run();
    joystick->handleJoystickMovements();
}

void SettingsMenuState::cleanup() {
    joystick->clearHandlers();
}

void SettingsMenuState::goBack() {
    stateManager->changeState<MainMenuState>();
}

void SettingsMenuState::goToLevel() {
    // TODO
}

void SettingsMenuState::goToLCD() {
    stateManager->changeState<SettingsLCDMenuState>();
}

void SettingsMenuState::goToMatrix() {
    stateManager->changeState<SettingsMatrixMenuState>();
}