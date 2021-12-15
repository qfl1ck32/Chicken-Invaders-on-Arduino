#include "./SettingsLevelMenuState.h"

#include "../../globals.h"

void SettingsLevelMenuState::setup() {
    static const char *const messages[] = {"Go back", "Increase lvl", "Decrease lvl"};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {SettingsLevelMenuState::goBack, SettingsLevelMenuState::increaseLevel, SettingsLevelMenuState::decreaseLevel};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);
}

void SettingsLevelMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsLevelMenuState::cleanup() {
    joystick.clearHandlers();
}

void SettingsLevelMenuState::goBack() {
    stateManager.changeState(settingsMenuStateId);
}

void SettingsLevelMenuState::increaseLevel() {
    game.changeLevel(game.level + 1);
}

void SettingsLevelMenuState::decreaseLevel() {
    game.changeLevel(game.level - 1);
}