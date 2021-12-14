#ifndef YouWonState_h
#define YouWonState_h

#include "../../../delayer/Delayer.h"
#include "../../../state/State.h"
#include "../../../utils/utils.h"
#include "../PlayingState/PlayingState.h"

class YouWonState : public State {
   public:
    Delayer delayer = Delayer(350);

    void setup();
    void handle();
    void cleanup();

    static void goToNextLevel();
};

#endif
