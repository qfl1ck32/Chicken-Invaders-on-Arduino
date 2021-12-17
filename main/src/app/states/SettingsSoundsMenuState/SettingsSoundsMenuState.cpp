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
    static const char *const messagesTurnOff[] PROGMEM = {backMessage, SettingsSoundsMenuState::turnMusicOff};
    static const char *const messagesTurnOn[] PROGMEM = {backMessage, SettingsSoundsMenuState::turnMusicOn};

    static byte numberOfMessages = sizeof(messagesTurnOn) / sizeof(char *);

    char **msgs = readArrayOfStringsFromPROGMEM(usesMusic ? messagesTurnOff : messagesTurnOn, numberOfMessages);

    menu.setMessages(msgs, numberOfMessages, isFirst);
}

void SettingsSoundsMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void SettingsSoundsMenuState::cleanup() {
    joystick.clearHandlers();

    matrix->setAllLeds(false);
}

void SettingsSoundsMenuState::goBack() {
    stateManager.changeState<SettingsMenuState>();
}

void SettingsSoundsMenuState::switchMusicPlaying() {
    usesMusic = !usesMusic;

    EEPROM.write(EEPROM_MUSIC_PLAYING_INDEX, usesMusic);

    SettingsSoundsMenuState::setMessages(false);
}