#pragma once

#include "../MainMenuState/MainMenuState.h"

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
