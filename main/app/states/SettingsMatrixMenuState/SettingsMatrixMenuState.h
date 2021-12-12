#pragma once

#include "../../../state/State.h"

class SettingsMatrixMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();
    static void increaseIntensity();
    static void decreaseIntensity();
};
