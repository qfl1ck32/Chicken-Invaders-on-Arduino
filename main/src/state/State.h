#ifndef State_h
#define State_h

#include "Arduino.h"

class State {
   public:
    virtual void setup() = 0;
    virtual void handle() = 0;
    virtual void cleanup() = 0;

    State() {}

    virtual ~State() {}
};

#endif
