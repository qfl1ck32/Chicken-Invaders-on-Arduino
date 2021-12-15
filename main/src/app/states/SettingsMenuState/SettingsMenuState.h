#ifndef SettingsMenuState_h
#define SettingsMenuState_h

#include "../../../state/State.h"

class SettingsMenuState : public State {
   public:
    SettingsMenuState(byte id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void goBack();

    static void goToLevel();

    static void goToLCD();

    static void goToMatrix();
};

#endif
