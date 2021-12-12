#pragma once

#include "../../../state/State.h"

class GameOverState : public State {
   public:
    Delayer delayer = Delayer(500);

    void setup();
    void handle();
    void cleanup();

    static void goToNextStep();
};
