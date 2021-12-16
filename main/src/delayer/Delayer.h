#ifndef Delayer_h
#define Delayer_h

#include "Arduino.h"

class Delayer {
   public:
    unsigned int lastTime = 0;

    unsigned int interval;

    bool isInCooldown = false;

    Delayer(unsigned int);

    Delayer();

    bool canRun();

    void updateInterval(unsigned int);
};

#endif
