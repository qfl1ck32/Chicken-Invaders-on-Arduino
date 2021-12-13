class Button {
   public:
    byte pin;

    bool previousButtonState = LOW;
    bool state = LOW;

    void (*onStateChange)();

    Button(byte pin) {
        this->pin = pin;

        this->onStateChange = nullptr;
    }

    void setup(void (*)());
    void setOnStateChange(void (*)());

    void clearHandler();

    static void handleStateChange(Button *);
};

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

void Button::handleStateChange(Button *button) {
    button->state = !button->state;

    if (button->onStateChange) button->onStateChange();
}