#ifndef MainMenuState_h
#define MainMenuState_h

#include "../../../state/State.h"

class AboutMenuState;
class LeaderboardState;
class SettingsMenuState;

class MainMenuState : public State {
   public:
    MainMenuState(byte id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void goToPlay();

    static void goToSettings();

    static void goToLeaderboard();

    static void goToAbout();
};

#endif
