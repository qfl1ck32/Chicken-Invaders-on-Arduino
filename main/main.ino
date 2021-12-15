// #include <app_api.h>
// #include <avr_debugger.h>

#include "src/app/globals.h"
#include "src/app/states/AboutMenuState/AboutMenuState.h"
#include "src/app/states/GameOverState/GameOverState.h"
#include "src/app/states/LeaderboardState/LeaderboardState.h"
#include "src/app/states/MainMenuState/MainMenuState.h"
#include "src/app/states/NameSelectionState/NameSelectionState.h"
#include "src/app/states/PlayingState/PlayingState.h"
#include "src/app/states/SettingsLCDMenuState/SettingsLCDMenuState.h"
#include "src/app/states/SettingsMatrixMenuState/SettingsMatrixMenuState.h"
#include "src/app/states/SettingsMenuState/SettingsMenuState.h"
#include "src/app/states/WelcomeState/WelcomeState.h"
#include "src/app/states/YouWonState/YouWonState.h"
#include "src/constants/app.h"
#include "src/modules/music-player/MusicPlayer.h"
#include "src/modules/music-player/songs.h"

Delayer buttonDelayer = Delayer(150);
Delayer swDelayer = Delayer(300);

// MusicPlayer musicPlayer = MusicPlayer(songBuzzer);

void handleSw() {
    if (swDelayer.canRun()) Joystick::swHandler(joystick);
}

void handleButtonStateChange() {
    if (buttonDelayer.canRun()) Button::handleStateChange(button);
}

void setup() {
    Serial.begin(baudRate);

    joystick.setup(handleSw);
    button.setup(handleButtonStateChange);
    lcd->setup(ledRows, ledColumns);

    lcd->createChar(heartChar, heartCharArray);

    matrix->setup();

    // stateManager.addState(new WelcomeState(welcomeStateId));
    // stateManager.addState(new AboutMenuState(aboutMenuStateId));
    // stateManager.addState(new GameOverState(gameOverStateId));
    stateManager.addState(new PlayingState(playingStateId));
    stateManager.addState(new MainMenuState(mainMenuStateId));
    stateManager.addState(new YouWonState(youWonStateId));
    // stateManager.addState(new LeaderboardState(leaderboardStateId));
    stateManager.addState(new SettingsMenuState(settingsMenuStateId));
    // stateManager.addState(new SettingsMatrixMenuState(settingsMatrixMenuStateId));
    // stateManager.addState(new SettingsLCDMenuState(settingsLCDMenuStateId));
    // stateManager.addState(new NameSelectionState(nameSelectionStateId));

    // musicPlayer.setSong(merryChristmas, sizeof(merryChristmas) / sizeof(int));

    // musicPlayer.setRepeat(true);

    // TODO:  maybe create a class ? 0 is not connected

    // for (int i = 0; i < 1024; ++i) {
    //     EEPROM.write(i, 255);
    // }

    randomSeed(analogRead(0));

    stateManager.changeState(playingStateId);
}

void loop() {
    // musicPlayer.play();
    stateManager.handle();
}
