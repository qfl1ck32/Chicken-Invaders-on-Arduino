#ifndef State_h
#define State_h

#include "Arduino.h"

class State {
   public:
    byte id;

    virtual void setup() = 0;
    virtual void handle() = 0;
    virtual void cleanup() = 0;

    State(byte id) { this->id = id; }

    virtual ~State() {}
};

#endif
