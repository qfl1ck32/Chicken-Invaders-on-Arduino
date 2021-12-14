#ifndef Delayer_h
#define Delayer_h

#include "Arduino.h"

class Delayer {
   public:
    unsigned long lastTime = 0;

    unsigned long interval;

    bool isInCooldown = false;

    Delayer(unsigned long interval) {
        this->interval = interval;
    }

    bool canRun();

    void updateInterval(unsigned long);
};

#endif
