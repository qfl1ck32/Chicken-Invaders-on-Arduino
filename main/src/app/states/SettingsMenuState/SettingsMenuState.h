#ifndef SettingsMenuState_h
#define SettingsMenuState_h

#include "../../../state/State.h"
#include "../../states/SettingsLCDMenuState/SettingsLCDMenuState.h"
#include "../../states/SettingsLevelMenuState/SettingsLevelMenuState.h"
#include "../../states/SettingsMatrixMenuState/SettingsMatrixMenuState.h"
#include "../../states/SettingsSoundsMenuState/SettingsSoundsMenuState.h"

class SettingsMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goToLevel();

    static void goToLCD();

    static void goToMatrix();

    static void goToSounds();
};

#endif
