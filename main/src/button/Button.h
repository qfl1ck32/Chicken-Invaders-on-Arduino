#ifndef Button_h
#define Button_h

#include "../app/typedefs.h"
#include "Arduino.h"

class Button {
   public:
    int8_t pin;

    bool previousButtonState = LOW;
    bool state = LOW;

    HandlerFunction onStateChange;

    Button(int8_t pin) {
        this->pin = pin;

        this->onStateChange = nullptr;
    }

    void setup(HandlerFunction);
    void setOnStateChange(HandlerFunction);

    void clearHandler();

    static void handleStateChange(Button &);
};

#endif
