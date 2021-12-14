#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"

class Buzzer {
   public:
    byte pin;

    Buzzer(byte);

    void buzz(unsigned int, unsigned long);
    void stop();
};

#endif
