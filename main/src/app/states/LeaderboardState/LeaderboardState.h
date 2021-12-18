#ifndef LeaderboardState_h
#define LeaderboardState_h

#include "../../../leaderboard/Leaderboard.h"
#include "../../../state/State.h"

class LeaderboardState : public State {
   public:
    Leaderboard *leaderboard;

    LeaderboardState();
    ~LeaderboardState();

    void setup();
    void handle();
    void cleanup();

    static void goBack();
};

#endif
