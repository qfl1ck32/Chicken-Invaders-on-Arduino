#ifndef PlayingState_h
#define PlayingState_h

#include "../../../state/State.h"
#include "../../../unit/Unit.h"

class PlayingState : public State {
   public:
    PlayingState(byte id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void moveUp();

    static void moveRight();

    static void moveDown();

    static void moveLeft();

    static void attack();
};

#endif
