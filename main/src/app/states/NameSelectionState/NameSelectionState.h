#ifndef NameSelectionState_h
#define NameSelectionState_h

#include "../../../state/State.h"

class NameSelectionState : public State {
   public:
    NameSelectionState(int8_t id) : State(id) {}

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
