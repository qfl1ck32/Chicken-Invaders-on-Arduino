#ifndef Buzzer_h
#define Buzzer_h

#include "Arduino.h"

class Buzzer {
   public:
    int8_t pin;

    Buzzer(int8_t);

    void buzz(unsigned int, unsigned int);
    void stop();
};

#endif
