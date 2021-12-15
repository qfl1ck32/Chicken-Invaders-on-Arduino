#ifndef SettingsLCDMenuState_h
#define SettingsLCDMenuState_h

#include <avr/pgmspace.h>

#include "../../../state/State.h"

class SettingsLCDMenuState : public State {
   public:
    SettingsLCDMenuState(byte id) : State(id) {}

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
