#ifndef WelcomeState_h
#define WelcomeState_h

#include "../../../state/State.h"
#include "../MainMenuState/MainMenuState.h"

class MainMenuState;

class WelcomeState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void moveToEnterYourNameState();
};

#endif
