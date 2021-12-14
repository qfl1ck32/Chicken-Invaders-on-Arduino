#ifndef Button_h
#define Button_h

#include "Arduino.h"

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

#endif
