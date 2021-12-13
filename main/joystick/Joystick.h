class Joystick {
   public:
    byte pinSw;
    short pinX;
    short pinY;

    Joystick(byte pinSw, short pinX, short pinY) {
        this->pinSw = pinSw;
        this->pinX = pinX;
        this->pinY = pinY;

        this->handlerXAxisChangeLeft = nullptr;
        this->handlerXAxisChangeRight = nullptr;

        this->handlerYAxisChangeUp = nullptr;
        this->handlerYAxisChangeDown = nullptr;
    }

    bool swState = false;

    void setup(void (*swHandler)());

    void handleJoystickMovements();
    void clearHandlers();

    void clearHandlerSwStateChange();

    void setHandlerOnXAxisChangeLeft(void (*)());
    void setHandlerOnXAxisChangeRight(void (*)());

    void setHandlerOnYAxisChangeUp(void (*)());
    void setHandlerOnYAxisChangeDown(void (*)());

    void setHandlerSwStateChange(void (*)());

    void handleJoystickMovementOnAxisY();
    void handleJoystickMovementOnAxisX();

    void handleSw();

    void (*handlerXAxisChangeLeft)();
    void (*handlerXAxisChangeRight)();

    void (*handlerYAxisChangeUp)();
    void (*handlerYAxisChangeDown)();

    void (*handlerSwStateChange)();

    bool joyMovedOnXAxis = false;
    bool joyMovedOnYAxis = false;

    int minThreshold = 400;
    int maxThreshold = 600;

    static void swHandler(Joystick *);
};

void Joystick::setup(void (*swHandler)()) {
    pinMode(this->pinSw, INPUT_PULLUP);
    pinMode(this->pinX, INPUT);
    pinMode(this->pinY, INPUT);

    attachInterrupt(digitalPinToInterrupt(pinSW), swHandler, FALLING);
}

void Joystick::clearHandlerSwStateChange() {
    this->handlerSwStateChange = nullptr;
}

void Joystick::setHandlerSwStateChange(void (*f)()) {
    this->handlerSwStateChange = f;
}

void Joystick::setHandlerOnXAxisChangeLeft(void (*f)()) {
    this->handlerXAxisChangeLeft = f;
}

void Joystick::setHandlerOnXAxisChangeRight(void (*f)()) {
    this->handlerXAxisChangeRight = f;
}

void Joystick::setHandlerOnYAxisChangeUp(void (*f)()) {
    this->handlerYAxisChangeUp = f;
}

void Joystick::setHandlerOnYAxisChangeDown(void (*f)()) {
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
