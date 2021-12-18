#include "src/app/globals.h"
#include "src/app/states/PlayingState/PlayingState.h"
#include "src/app/states/WelcomeState/WelcomeState.h"
#include "src/constants/app.h"
#include "src/music-player/MusicPlayer.h"
#include "src/music-player/songs.h"

Delayer buttonDelayer = Delayer(200);
Delayer swDelayer = Delayer(200);

MusicPlayer musicPlayer = MusicPlayer(songBuzzer);

void handleSw() {
    if (swDelayer.canRun()) Joystick::swHandler(joystick);
}

void handleButtonStateChange() {
    if (buttonDelayer.canRun()) Button::handleStateChange(button);
}

void setup() {
    // for (int i = 0; i < 256; ++i) {
    //     EEPROM.write(i, 255);
    // }

    Serial.begin(baudRate);

    joystick.setup(handleSw);
    button.setup(handleButtonStateChange);

    lcd->setup(ledRows, ledColumns);
    // lcd->createChar(heartChar, heartCharArray);

    matrix->setup();

    lcd->clear();
    matrix->setAllLeds(false);

    musicPlayer.setSong(silentNight, sizeof(silentNight) / sizeof(silentNight[0]));
    musicPlayer.setRepeat(true);

    stateManager.changeState<WelcomeState>();

    initialiseRandomSeed();
}

void loop() {
    if (usesMusic) {
        musicPlayer.play();
    }

    stateManager.handle();
}
