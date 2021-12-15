#ifndef GameOverState_h
#define GameOverState_h

#include "../../../constants/app.h"
#include "../../../delayer/Delayer.h"
#include "../../../state/State.h"
#include "../../../utils/utils.h"

class GameOverState : public State {
   public:
    Delayer delayer = Delayer(500);

    GameOverState(byte id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void goToNextStep();
};

#endif
