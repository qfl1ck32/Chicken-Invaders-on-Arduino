#pragma once

#include "../../../state/State.h"

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
