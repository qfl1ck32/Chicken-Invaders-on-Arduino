#include "./SettingsSoundsMenuState.h"

#include "../../globals.h"

const char SettingsSoundsMenuState::turnMusicOn[] PROGMEM = "Turn music on";
const char SettingsSoundsMenuState::turnMusicOff[] PROGMEM = "Turn music off";

void SettingsSoundsMenuState::setup() {
    static const uint64_t icon PROGMEM = 0x0406354545350604;
    SettingsSoundsMenuState::setMessages(true);

    HandlerFunction handlers[] = {SettingsSoundsMenuState::goBack, SettingsSoundsMenuState::switchMusicPlaying};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    uint64_t image = readImageFromPROGMEM(&icon);

    matrix->displayImage(image);
}

void SettingsSoundsMenuState::setMessages(bool isFirst) {
    // TODO: refactor the logic for messages in menus, generally. please.
    static const char *const messages[] PROGMEM = {backMessage, usesMusic ? SettingsSoundsMenuState::turnMusicOff : SettingsSoundsMenuState::turnMusicOff};

    menu.setMessages(messages, sizeof(messages) / sizeof(char *), isFirst);
}

void SettingsSoundsMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsSoundsMenuState::cleanup() {
    joystick.clearHandlers();

    matrix->clear();
}

void SettingsSoundsMenuState::goBack() {
    stateManager.changeState(settingsMenuStateId);
}

void SettingsSoundsMenuState::switchMusicPlaying() {
    usesMusic = !usesMusic;

    EEPROM.write(EEPROM_MUSIC_PLAYING_INDEX, usesMusic);

    SettingsSoundsMenuState::setMessages(false);
}