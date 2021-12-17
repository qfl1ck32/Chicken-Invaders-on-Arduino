#ifndef SettingsMatrixMenuState_h
#define SettingsMatrixMenuState_h

#include <avr/pgmspace.h>

#include "../../../state/State.h"
#include "../../states/SettingsMenuState/SettingsMenuState.h"

class SettingsMatrixMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();
    static void increaseIntensity();
    static void decreaseIntensity();
};

#endif
