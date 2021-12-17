#ifndef LeaderboardState_h
#define LeaderboardState_h

#include "../../../state/State.h"

class LeaderboardState : public State {
   public:
    LeaderboardState(int8_t id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void goBack();
};

#endif
