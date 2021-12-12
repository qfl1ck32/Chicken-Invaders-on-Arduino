#pragma once

#include "../../../state/State.h"

class LeaderboardState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();
};
