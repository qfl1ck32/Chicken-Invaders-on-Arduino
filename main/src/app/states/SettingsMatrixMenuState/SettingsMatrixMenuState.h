#ifndef SettingsMatrixMenuState_h
#define SettingsMatrixMenuState_h

#include <avr/pgmspace.h>

#include "../../../state/State.h"

class SettingsMatrixMenuState : public State {
   public:
    SettingsMatrixMenuState(byte id) : State(id) {}

    void setup();
    void handle();
    void cleanup();

    static void goBack();
    static void increaseIntensity();
    static void decreaseIntensity();
};

#endif
