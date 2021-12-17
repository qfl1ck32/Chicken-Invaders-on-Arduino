#ifndef NameSelectionState_h
#define NameSelectionState_h

#include "../../../leaderboard/Leaderboard.h"
#include "../../../name-selection/NameSelector.h"
#include "../../../state/State.h"
#include "../../states/MainMenuState/MainMenuState.h"

class NameSelectionState : public State {
   public:
    NameSelectionState();

    ~NameSelectionState();

    static Leaderboard *leaderboard;

    static NameSelector *nameSelector;

    void setup();
    void handle();
    void cleanup();

    static void goUp();

    static void goDown();

    static void goLeft();

    static void goRight();

    static void handleSwStateChange();

    static void finish();
};

#endif
