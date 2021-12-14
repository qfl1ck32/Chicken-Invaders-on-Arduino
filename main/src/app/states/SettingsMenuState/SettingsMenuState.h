#ifndef SettingsMenuState_h
#define SettingsMenuState_h

#include "../../../state/State.h"
#include "../MainMenuState/MainMenuState.h"
#include "../SettingsLCDMenuState/SettingsLCDMenuState.h"
#include "../SettingsMatrixMenuState/SettingsMatrixMenuState.h"

class MainMenuState;
class SettingsLCDMenuState;
class SettingsMatrixMenuState;

class SettingsMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();

    static void goToLevel();

    static void goToLCD();

    static void goToMatrix();
};

#endif
