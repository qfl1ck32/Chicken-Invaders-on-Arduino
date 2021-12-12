#pragma once

#include "../../../state/State.h"

class MainMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goToPlay();

    static void goToSettings();

    static void goToLeaderboard();

    static void goToAbout();
};
