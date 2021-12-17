#ifndef SettingsMenuState_h
#define SettingsMenuState_h

#include "../../../state/State.h"

class SettingsMenuState : public State {
   public:
    SettingsMenuState(int8_t id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void goBack();

    static void goToLevel();

    static void goToLCD();

    static void goToMatrix();

    static void goToSounds();
};

#endif
