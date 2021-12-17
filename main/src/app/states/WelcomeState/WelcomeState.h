#ifndef WelcomeState_h
#define WelcomeState_h

#include "../../../delayer/Delayer.h"
#include "../../../state/State.h"
#include "../../states/MainMenuState/MainMenuState.h"

class WelcomeState : public State {
   public:
    Delayer delayer;

    WelcomeState();

    void setup();
    void handle();
    void cleanup();

    static void moveToEnterYourNameState();
};

#endif
