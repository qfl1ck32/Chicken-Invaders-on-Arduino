#ifndef SettingsSoundsMenuState_h
#define SettingsSoundsMenuState_h

#include "../../../state/State.h"
#include "../../states/SettingsMenuState/SettingsMenuState.h"

class SettingsSoundsMenuState : public State {
   public:
    void setup();
    void handle();
    void cleanup();

    static void goBack();

    static void increaseContrast();

    static void decreaseContrast();

    static void increaseBacklight();

    static void decreaseBacklight();

    static void switchMusicPlaying();

    static const char turnMusicOn[];
    static const char turnMusicOff[];

    static void setMessages(bool);
};

#endif
