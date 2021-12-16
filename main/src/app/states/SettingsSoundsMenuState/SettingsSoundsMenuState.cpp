#include "./SettingsSoundsMenuState.h"

#include "../../globals.h"

const char SettingsSoundsMenuState::turnMusicOn[] PROGMEM = "Turn music on";
const char SettingsSoundsMenuState::turnMusicOff[] PROGMEM = "Turn music off";

void SettingsSoundsMenuState::setup() {
    SettingsSoundsMenuState::setMessages();

    HandlerFunction handlers[] = {SettingsSoundsMenuState::goBack, SettingsSoundsMenuState::switchMusicPlaying};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);
}

void SettingsSoundsMenuState::setMessages() {
    static const char *const messages[] = {backMessage, usesMusic ? SettingsSoundsMenuState::turnMusicOff : SettingsSoundsMenuState::turnMusicOff};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *));
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

    SettingsSoundsMenuState::setMessages();
}