#ifndef MainMenuState_h
#define MainMenuState_h

#include "../../../state/State.h"
#include "../AboutMenuState/AboutMenuState.h"
#include "../LeaderboardState/LeaderboardState.h"
#include "../PlayingState/PlayingState.h"
#include "../SettingsMenuState/SettingsMenuState.h"

class AboutMenuState;
class LeaderboardState;
class SettingsMenuState;

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

#endif
