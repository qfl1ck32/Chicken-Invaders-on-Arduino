#include "./Joystick.h"

void Joystick::setup(HandlerFunction swHandler) {
    pinMode(this->pinSw, INPUT_PULLUP);
    pinMode(this->pinX, INPUT);
    pinMode(this->pinY, INPUT);

    attachInterrupt(digitalPinToInterrupt(this->pinSw), swHandler, FALLING);
}

void Joystick::clearHandlerSwStateChange() {
    this->handlerSwStateChange = nullptr;
}

void Joystick::setHandlerSwStateChange(HandlerFunction f) {
    this->handlerSwStateChange = f;
}

void Joystick::setHandlerOnXAxisChangeLeft(HandlerFunction f) {
    this->handlerXAxisChangeLeft = f;
}

void Joystick::setHandlerOnXAxisChangeRight(HandlerFunction f) {
    this->handlerXAxisChangeRight = f;
}

void Joystick::setHandlerOnYAxisChangeUp(HandlerFunction f) {
    this->handlerYAxisChangeUp = f;
}

void Joystick::setHandlerOnYAxisChangeDown(HandlerFunction f) {
    this->handlerYAxisChangeDown = f;
}

void Joystick::handleJoystickMovementOnAxisY() {
    int yValue = analogRead(pinY);

    if (yValue < this->minThreshold && !this->joyMovedOnYAxis) {
        this->joyMovedOnYAxis = true;

        if (this->handlerYAxisChangeUp) this->handlerYAxisChangeUp();
    }

    if (yValue > this->maxThreshold && !this->joyMovedOnYAxis) {
        this->joyMovedOnYAxis = true;

        if (this->handlerYAxisChangeDown) this->handlerYAxisChangeDown();
    }

    if (yValue >= this->minThreshold && yValue <= this->maxThreshold) {
        this->joyMovedOnYAxis = false;
    }
}

void Joystick::handleJoystickMovementOnAxisX() {
    int xValue = analogRead(pinX);

    if (xValue < this->minThreshold && !this->joyMovedOnXAxis) {
        this->joyMovedOnXAxis = true;

        if (this->handlerXAxisChangeLeft) this->handlerXAxisChangeLeft();
    }

    if (xValue > this->maxThreshold && !this->joyMovedOnXAxis) {
        this->joyMovedOnXAxis = true;

        if (this->handlerXAxisChangeRight) this->handlerXAxisChangeRight();
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
    this->handlerXAxisChangeLeft = nullptr;
    this->handlerXAxisChangeRight = nullptr;
    this->handlerYAxisChangeDown = nullptr;
    this->handlerYAxisChangeUp = nullptr;

    this->handlerSwStateChange = nullptr;
}

void Joystick::swHandler(Joystick *joystick) {
    bool currentSwState = digitalRead(joystick->pinSw);

    joystick->swState = !joystick->swState;
    if (joystick->handlerSwStateChange) joystick->handlerSwStateChange();
}
