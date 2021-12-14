#include "./Button.h"

void Button::setup(void (*onStateChangeHandler)()) {
    pinMode(this->pin, INPUT_PULLUP);
    attachInterrupt(digitalPinToInterrupt(this->pin), onStateChangeHandler, FALLING);
}

void Button::clearHandler() {
    this->onStateChange = nullptr;
}

void Button::setOnStateChange(void (*onStateChange)()) {
    this->onStateChange = onStateChange;
}

void Button::handleStateChange(Button &button) {
    button.state = !button.state;

    if (button.onStateChange) button.onStateChange();
}