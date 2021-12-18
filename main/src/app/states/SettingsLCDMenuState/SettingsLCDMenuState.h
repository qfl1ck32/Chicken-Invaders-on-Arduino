#ifndef SettingsLCDMenuState_h
#define SettingsLCDMenuState_h

#include "../../../state/State.h"
#include "../../states/SettingsMenuState/SettingsMenuState.h"

class SettingsLCDMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void increaseContrast();

    static void decreaseContrast();

    static void increaseBacklight();

    static void decreaseBacklight();
};

#endif
