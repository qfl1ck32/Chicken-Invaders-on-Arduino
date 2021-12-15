#ifndef YouWonState_h
#define YouWonState_h

#include "../../../delayer/Delayer.h"
#include "../../../state/State.h"
#include "../../../utils/utils.h"

class YouWonState : public State {
   public:
    Delayer delayer = Delayer(350);

    YouWonState(byte id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void goToNextLevel();
};

#endif
