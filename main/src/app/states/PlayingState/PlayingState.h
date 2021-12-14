#ifndef PlayingState_h
#define PlayingState_h

#include "../../../state/State.h"

class PlayingState : public State {
   public:
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
