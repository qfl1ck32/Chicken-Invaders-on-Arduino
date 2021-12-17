#ifndef LeaderboardState_h
#define LeaderboardState_h

#include "../../../state/State.h"
#include "../../states/MainMenuState/MainMenuState.h"

class LeaderboardState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();
};

#endif
