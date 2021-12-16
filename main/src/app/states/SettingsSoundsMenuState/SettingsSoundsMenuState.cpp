#include "./SettingsSoundsMenuState.h"

#include "../../globals.h"

void SettingsSoundsMenuState::setup() {
    static const char *const messages[] = {"Go back", usesMusic ? "Turn music off" : "Turn music on"};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));

    HandlerFunction handlers[] = {SettingsSoundsMenuState::goBack, SettingsSoundsMenuState::switchMusicPlaying};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);
}

void SettingsSoundsMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsSoundsMenuState::cleanup() {
    joystick.clearHandlers();
}

void SettingsSoundsMenuState::goBack() {
    stateManager.changeState(settingsMenuStateId);
}

void SettingsSoundsMenuState::switchMusicPlaying() {
    usesMusic = !usesMusic;

    EEPROM.write(EEPROM_MUSIC_PLAYING_INDEX, usesMusic);

    // FIXME: dry
    const char *const messages[] = {"Go back", usesMusic ? "Turn music off" : "Turn music on"};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));
}