#pragma once

#include "../../../state/State.h"

class WelcomeState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void moveToEnterYourNameState();
};
