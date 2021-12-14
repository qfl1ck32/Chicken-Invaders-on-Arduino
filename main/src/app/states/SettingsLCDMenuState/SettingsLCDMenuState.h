#ifndef SettingsLCDMenuState_h
#define SettingsLCDMenuState_h

#include <avr/pgmspace.h>

#include "../../../state/State.h"
#include "../SettingsMenuState/SettingsMenuState.h"

class SettingsMenuState;

class SettingsLCDMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();

    static void increaseContrast();

    static void decreaseContrast();

    static void increaseBacklight();

    static void decreaseBacklight();
};

#endif
