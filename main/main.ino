// #include <app_api.h>
// #include <avr_debugger.h>

#include "src/app/globals.h"
#include "src/app/states/MainMenuState/MainMenuState.h"
#include "src/app/states/PlayingState/PlayingState.h"
#include "src/app/states/WelcomeState/WelcomeState.h"
#include "src/constants/app.h"
#include "src/lcd/LCD.h"
#include "src/modules/music-player/MusicPlayer.h"
#include "src/modules/music-player/songs.h"

Delayer buttonDelayer = Delayer(150);
Delayer swDelayer = Delayer(300);

MusicPlayer musicPlayer = MusicPlayer(songBuzzer);

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

    stateManager->changeState<WelcomeState>();

    musicPlayer.setSong(merryChristmas, sizeof(merryChristmas) / sizeof(int));

    musicPlayer.setRepeat(true);

    // TODO:  maybe create a class ? 0 is not connected

    // for (int i = 0; i < 1024; ++i) {
    //     EEPROM.write(i, 255);
    // }

    randomSeed(analogRead(0));
}

void loop() {
    musicPlayer.play();
    stateManager->handle();
}
