// #include <app_api.h>
// #include <avr_debugger.h>

#include "./app/app.h"
#include "./app/states/PlayingState/PlayingState.cpp"
#include "./app/states/WelcomeState/WelcomeState.cpp"

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

    stateManager->changeState<PlayingState>();
}

void loop() {
    stateManager->handle();
}
