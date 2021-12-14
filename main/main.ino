// #include <app_api.h>
// #include <avr_debugger.h>

// #include "./app/globals.h"
// #include "./app/states/WelcomeState/WelcomeState.h"
// #include "./modules/music-player/MusicPlayer.h"
// #include "./modules/music-player/songs.h"

// #include "src/state-manager/StateManager.h"

// Delayer buttonDelayer = Delayer(150);
// Delayer swDelayer = Delayer(300);

// MusicPlayer musicPlayer = MusicPlayer(songBuzzer);

// void handleSw() {
//     if (swDelayer.canRun()) Joystick::swHandler(joystick);
// }

// void handleButtonStateChange() {
//     if (buttonDelayer.canRun()) Button::handleStateChange(button);
// }

// StateManager *stateManager = new StateManager();

void setup() {
    // Serial.begin(baudRate);

    // joystick->setup(handleSw);
    // button->setup(handleButtonStateChange);
    // lcd->setup(ledRows, ledColumns);

    // lcd->createChar(heartChar, heartCharArray);

    // matrix->setup();

    // new WelcomeState();

    // stateManager->changeState<WelcomeState>();

    // musicPlayer.setSong(merryChristmas, sizeof(merryChristmas) / sizeof(int));

    // musicPlayer.setRepeat(true);

    // TODO:  maybe create a class ? 0 is not connected
    // randomSeed(analogRead(0));
}

void loop() {
    // Serial.println(millis());
    // musicPlayer.play();
    // stateManager->handle();
}
