// #include <app_api.h>
// #include <avr_debugger.h>

#include "src/app/globals.h"
#include "src/app/states/PlayingState/PlayingState.h"
#include "src/app/states/WelcomeState/WelcomeState.h"
#include "src/constants/app.h"
#include "src/music-player/MusicPlayer.h"
#include "src/music-player/songs.h"

Delayer buttonDelayer = Delayer(300);
Delayer swDelayer = Delayer(300);

GameEngine* Unit::engine = new GameEngine(MATRIX_ROWS, MATRIX_COLUMNS);

MusicPlayer musicPlayer = MusicPlayer(songBuzzer);

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
    // lcd->createChar(heartChar, heartCharArray);

    matrix->setup();

    lcd->clear();
    matrix->setAllLeds(false);

    musicPlayer.setSong(merryChristmas, sizeof(merryChristmas) / sizeof(merryChristmas[0]));
    musicPlayer.setRepeat(true);

    stateManager.changeState<MainMenuState>();

    initialiseRandomSeed();
}

void loop() {
    if (usesMusic) {
        musicPlayer.play();
    }

    stateManager.handle();
}
