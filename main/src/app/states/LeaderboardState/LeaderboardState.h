#ifndef LeaderboardState_h
#define LeaderboardState_h

#include "../../../state/State.h"
#include "../MainMenuState/MainMenuState.h"
#include "LinkedList.h"

class LeaderboardState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();
};

#endif
