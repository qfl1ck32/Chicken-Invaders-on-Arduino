#ifndef WelcomeState_h
#define WelcomeState_h

#include "../../../delayer/Delayer.h"
#include "../../../state/State.h"

class WelcomeState : public State {
   public:
    Delayer delayer = Delayer(350);

    WelcomeState(int8_t id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void moveToEnterYourNameState();
};

#endif
