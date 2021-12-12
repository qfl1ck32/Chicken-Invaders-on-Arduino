#pragma once

#include "../../../state/State.h"

class YouWonState : public State {
   public:
    Delayer delayer = Delayer(350);

    void setup();
    void handle();
    void cleanup();

    static void goToNextLevel();
};
