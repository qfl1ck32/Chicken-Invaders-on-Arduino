#ifndef Greeter_h
#define Greeter_h

#include "../../delayer/Delayer.h"
#include "../../lcd/LCD.h"

class Greeter {
   public:
    LCD *lcd;
    const char *greeting;
    const char *introMessage;

    Delayer delayer = Delayer(350);

    Greeter(LCD *lcd, const char *greeting, const char *introMessage) {
        this->lcd = lcd;
        this->greeting = greeting;
        this->introMessage = introMessage;
    }

    void run();
};

#endif
