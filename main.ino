// #include <app_api.h>
// #include <avr_debugger.h>

#include "./app/app.h"
#include "./app/states/AboutMenuState.h"
#include "./app/states/GameOverState.h"
#include "./app/states/LeaderboardState.h"
#include "./app/states/MainMenuState.h"
#include "./app/states/NameSelectionState.h"
#include "./app/states/PlayingState.h"
#include "./app/states/SettingsMenuState.h"
#include "./app/states/WelcomeState.h"
#include "./app/states/YouWonState.h"

Delayer buttonDelayer = Delayer(150);
Delayer swDelayer = Delayer(150);

void handleSw() {
    if (swDelayer.canRun()) Joystick::swHandler(joystick);
}

void handleButtonStateChange() {
    if (buttonDelayer.canRun()) Button::handleStateChange(button);
}

void setup() {
    Serial.begin(baudRate);

    joystick->setup(handleSw);
    button->setup(handleButtonStateChange);
    lcd->setup(ledRows, ledColumns);

    lcd->createChar(heartChar, heartCharArray);

    matrix->setup();

    stateManager->addState(new WelcomeState(welcomeStateId));

    stateManager->addState(new NameSelectionState(nameSelectionStateId));

    stateManager->addState(new MainMenuState(mainMenuStateId));

    stateManager->addState(new SettingsMenuState(settingsMenuStateId));

    stateManager->addState(new LeaderboardState(leaderboardMenuStateId));

    stateManager->addState(new AboutMenuState(aboutMenuStateId));

    // TODO: remove all links to playingState -> ...
    stateManager->addState(playingState);

    stateManager->addState(new GameOverState(gameOverStateId));

    stateManager->addState(new YouWonState(youWonStateId));

    stateManager->changeState(aboutMenuStateId);
}

void loop() {
    stateManager->handle();
}
