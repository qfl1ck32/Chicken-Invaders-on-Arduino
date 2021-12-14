#ifndef NameSelectionState_h
#define NameSelectionState_h

#include "../MainMenuState/MainMenuState.h"
#include "../PlayingState/PlayingState.h"

class PlayingState;

class NameSelectionState : public State {
   public:
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
