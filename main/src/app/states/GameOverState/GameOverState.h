#ifndef GameOverState_h
#define GameOverState_h

#include "../../../constants/app.h"
#include "../../../delayer/Delayer.h"
#include "../../../state/State.h"
#include "../../../utils/utils.h"
#include "../MainMenuState/MainMenuState.h"
#include "../NameSelectionState/NameSelectionState.h"
#include "../PlayingState/PlayingState.h"

class GameOverState : public State {
   public:
    Delayer delayer = Delayer(500);

    void setup();
    void handle();
    void cleanup();

    static void goToNextStep();
};

#endif
