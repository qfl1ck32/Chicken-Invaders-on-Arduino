#ifndef SettingsLevelMenuState_h
#define SettingsLevelMenuState_h

#include <avr/pgmspace.h>

#include "../../../state/State.h"

class SettingsLevelMenuState : public State {
   public:
    SettingsLevelMenuState(byte id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void goBack();

    static void increaseLevel();

    static void decreaseLevel();

    static void showLevel();
};

#endif
