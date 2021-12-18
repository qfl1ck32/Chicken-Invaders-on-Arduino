#ifndef HowToPlayMenuState_h
#define HowToPlayMenuState_h

#include "../../../state/State.h"
#include "../../states/MainMenuState/MainMenuState.h"

class HowToPlayMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();
};

#endif
