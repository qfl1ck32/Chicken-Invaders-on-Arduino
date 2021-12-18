#include "./HowToPlayMenuState.h"

#include "../../globals.h"

void HowToPlayMenuState::setup() {
    static const char m1[] PROGMEM = "On the upmost";
    static const char m2[] PROGMEM = "two rows, we";
    static const char m3[] PROGMEM = "have chickens";
    static const char m4[] PROGMEM = "which move and";
    static const char m5[] PROGMEM = "drop eggs!";
    static const char m6[] PROGMEM = "Be careful!";
    static const char m7[] PROGMEM = "You are the";
    static const char m8[] PROGMEM = "spaceship in";
    static const char m9[] PROGMEM = "the first row!";
    static const char m10[] PROGMEM = "Use the joy to";
    static const char m11[] PROGMEM = "move, and";
    static const char m12[] PROGMEM = "press X to";
    static const char m13[] PROGMEM = "shoot bullets!";

    static const char gl[] PROGMEM = "Good luck!";
    static const char hf[] PROGMEM = "Have fun!";

    static const char *const messages[] PROGMEM = {backMessage, m1, m2, m3, m4, m5, m6, m7, m8, m9, m10, m11, m12, m13, gl, hf};
    static byte numberOfMessages = sizeof(messages) / sizeof(char *);

    static const uint64_t hammerImage PROGMEM = 0x00e7bd8181ff1818;

    char **msgs = readArrayOfStringsFromPROGMEM(messages, numberOfMessages);

    menu.setMessages(msgs, numberOfMessages);

    HandlerFunction handlers[] = {SettingsMenuState::goBack};

    menu.setOns(handlers, sizeof(handlers) / sizeof(HandlerFunction));

    joystick.setOnChangeUp(menuGoUp);
    joystick.setOnChangeDown(menuGoDown);

    joystick.setOnSwStateChange(menuSelect);

    uint64_t image = readImageFromPROGMEM(&hammerImage);

    matrix->displayImage(image);
}

void HowToPlayMenuState::handle() {
    menu.run();
    joystick.handleJoystickMovements();
}

void HowToPlayMenuState::cleanup() {
    joystick.clearHandlers();

    matrix->setAllLeds(false);
}

void HowToPlayMenuState::goBack() {
    stateManager.changeState<MainMenuState>();
}
