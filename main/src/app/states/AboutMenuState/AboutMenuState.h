#ifndef AboutMenuState_h
#define AboutMenuState_h

#include <avr/pgmspace.h>

#include "../../../state/State.h"
#include "../MainMenuState/MainMenuState.h"

class MainMenuState;

class AboutMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();
};

#endif
