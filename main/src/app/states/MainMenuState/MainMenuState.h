#ifndef MainMenuState_h
#define MainMenuState_h

#include "../../../state/State.h"
#include "../../states/AboutMenuState/AboutMenuState.h"
#include "../../states/HowToPlayMenuState/HowToPlayMenuState.h"
#include "../../states/LeaderboardState/LeaderboardState.h"
#include "../../states/PlayingState/PlayingState.h"
#include "../../states/SettingsMenuState/SettingsMenuState.h"

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

    static void goToHowToPlay();

    static void goToAbout();
};

#endif
