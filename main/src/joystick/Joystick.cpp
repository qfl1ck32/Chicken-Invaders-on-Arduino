#include "./Joystick.h"

void Joystick::setup(HandlerFunction swHandler) {
    pinMode(this->pinSw, INPUT_PULLUP);
    pinMode(this->pinX, INPUT);
    pinMode(this->pinY, INPUT);

    attachInterrupt(digitalPinToInterrupt(this->pinSw), swHandler, FALLING);
}

void Joystick::clearSwHandler() {
    this->handlerSwStateChange = nullptr;
}

void Joystick::setOnSwStateChange(HandlerFunction f) {
    this->handlerSwStateChange = f;
}

void Joystick::setOnChangeLeft(HandlerFunction f) {
    this->handlerChangeLeft = f;
}

void Joystick::setOnChangeRight(HandlerFunction f) {
    this->handlerChangeRight = f;
}

void Joystick::setOnChangeUp(HandlerFunction f) {
    this->handlerChangeUp = f;
}

void Joystick::setOnChangeDown(HandlerFunction f) {
    this->handlerChangeDown = f;
}

void Joystick::handleJoystickMovementOnAxisY() {
    int yValue = analogRead(pinY);

    if (yValue < this->minThreshold && !this->joyMovedOnYAxis) {
        this->joyMovedOnYAxis = true;

        if (this->handlerChangeUp) this->handlerChangeUp();
    }

    if (yValue > this->maxThreshold && !this->joyMovedOnYAxis) {
        this->joyMovedOnYAxis = true;

        if (this->handlerChangeDown) this->handlerChangeDown();
    }

    if (yValue >= this->minThreshold && yValue <= this->maxThreshold) {
        this->joyMovedOnYAxis = false;
    }
}

void Joystick::handleJoystickMovementOnAxisX() {
    int xValue = analogRead(pinX);

    if (xValue < this->minThreshold && !this->joyMovedOnXAxis) {
        this->joyMovedOnXAxis = true;

        if (this->handlerChangeLeft) this->handlerChangeLeft();
    }

    if (xValue > this->maxThreshold && !this->joyMovedOnXAxis) {
        this->joyMovedOnXAxis = true;

        if (this->handlerChangeRight) this->handlerChangeRight();
    }

    if (xValue >= this->minThreshold && xValue <= this->maxThreshold) {
        this->joyMovedOnXAxis = false;
    }
}

void Joystick::handleJoystickMovements() {
    this->handleJoystickMovementOnAxisX();
    this->handleJoystickMovementOnAxisY();
}

void Joystick::clearHandlers() {
    this->handlerChangeLeft = nullptr;
    this->handlerChangeRight = nullptr;
    this->handlerChangeDown = nullptr;
    this->handlerChangeUp = nullptr;

    this->handlerSwStateChange = nullptr;
}

void Joystick::swHandler(Joystick &joystick) {
    bool currentSwState = digitalRead(joystick.pinSw);

    joystick.swState = !joystick.swState;
    if (joystick.handlerSwStateChange) joystick.handlerSwStateChange();
}
