#include "./MainMenuState.h"

#include "../../globals.h"

void MainMenuState::setup() {
    static const char *const messages[] = {"Play", "Settings", "Leaderboard", "About"};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {MainMenuState::goToPlay, MainMenuState::goToSettings, MainMenuState::goToLeaderboard, MainMenuState::goToAbout};
    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);
}

void MainMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void MainMenuState::cleanup() {
    joystick.clearHandlers();
    button.clearHandler();

    lcd->clear();
}

void MainMenuState::goToPlay() {
    stateManager.changeState(playingStateId);
}

void MainMenuState::goToSettings() {
    stateManager.changeState(settingsMenuStateId);
}

void MainMenuState::goToLeaderboard() {
    stateManager.changeState(leaderboardStateId);
}

void MainMenuState::goToAbout() {
    stateManager.changeState(aboutMenuStateId);
}