#ifndef WelcomeState_h
#define WelcomeState_h

#include "../../../delayer/Delayer.h"
#include "../../../state/State.h"
#include "../MainMenuState/MainMenuState.h"

class WelcomeState : public State {
   public:
    Delayer delayer = Delayer(350);

    void setup();
    void handle();
    void cleanup();

    static void moveToEnterYourNameState();
};

#endif
