#include "./MainMenuState.h"

#include "../../globals.h"

void MainMenuState::setup() {
    static const char *const messages[] PROGMEM = {"Play", "Settings", "Leaderboard", "About"};

    menu->setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {MainMenuState::goToPlay, MainMenuState::goToSettings, MainMenuState::goToLeaderboard, MainMenuState::goToAbout};
    menu->setHandlers(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick->setHandlerOnYAxisChangeUp(menuGoUp);
    joystick->setHandlerOnYAxisChangeDown(menuGoDown);

    joystick->setHandlerSwStateChange(menuSelect);
}

void MainMenuState::handle() {
    menu->run();
    joystick->handleJoystickMovements();
}

void MainMenuState::cleanup() {
    joystick->clearHandlers();
    button->clearHandler();

    lcd->clear();
}

void MainMenuState::goToPlay() {
    stateManager->changeState<PlayingState>();
}

void MainMenuState::goToSettings() {
    stateManager->changeState<SettingsMenuState>();
}

void MainMenuState::goToLeaderboard() {
    stateManager->changeState<LeaderboardState>();
}

void MainMenuState::goToAbout() {
    stateManager->changeState<AboutMenuState>();
}