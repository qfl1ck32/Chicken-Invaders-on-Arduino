#ifndef SettingsLevelMenuState_h
#define SettingsLevelMenuState_h

#include "../../../state/State.h"
#include "../../states/SettingsMenuState/SettingsMenuState.h"

class SettingsLevelMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();

    static void increaseLevel();

    static void decreaseLevel();

    static void showLevel();
};

#endif
