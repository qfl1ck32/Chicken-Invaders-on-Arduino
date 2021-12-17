#ifndef State_h
#define State_h

#include "Arduino.h"

class State {
   public:
    int8_t id;

    virtual void setup() = 0;
    virtual void handle() = 0;
    virtual void cleanup() = 0;

    State(int8_t id) { this->id = id; }

    virtual ~State() {}
};

#endif
