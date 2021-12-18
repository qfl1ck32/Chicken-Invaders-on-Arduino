#ifndef AboutMenuState_h
#define AboutMenuState_h

#include <avr/pgmspace.h>

#include "../../../state/State.h"

class AboutMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();
};

#endif
