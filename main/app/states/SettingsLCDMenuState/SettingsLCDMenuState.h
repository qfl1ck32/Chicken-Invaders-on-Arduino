#pragma once

#include "../../../state/State.h"

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
