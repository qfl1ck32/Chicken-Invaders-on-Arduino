#ifndef HowToPlayMenuState_h
#define HowToPlayMenuState_h

#include "../../../state/State.h"

class HowToPlayMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();
};

#endif
