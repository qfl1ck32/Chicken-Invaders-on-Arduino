#ifndef Joystick_h
#define Joystick_h

#include "../app/typedefs.h"
#include "Arduino.h"

class Joystick {
   public:
    byte pinSw;
    byte pinX;
    byte pinY;

    Joystick(byte pinSw, byte pinX, byte pinY) {
        this->pinSw = pinSw;
        this->pinX = pinX;
        this->pinY = pinY;

        this->handlerChangeLeft = nullptr;
        this->handlerChangeRight = nullptr;

        this->handlerChangeUp = nullptr;
        this->handlerChangeDown = nullptr;
    }

    bool swState = false;

    void setup(HandlerFunction);

    void handleJoystickMovements();
    void clearHandlers();

    void clearSwHandler();

    void setOnChangeLeft(HandlerFunction);
    void setOnChangeRight(HandlerFunction);

    void setOnChangeUp(HandlerFunction);
    void setOnChangeDown(HandlerFunction);

    void setOnSwStateChange(HandlerFunction);

    void handleJoystickMovementOnAxisY();
    void handleJoystickMovementOnAxisX();

    void handleSw();

    void (*handlerChangeLeft)();
    void (*handlerChangeRight)();

    void (*handlerChangeUp)();
    void (*handlerChangeDown)();

    void (*handlerSwStateChange)();

    bool joyMovedOnXAxis = false;
    bool joyMovedOnYAxis = false;

    short minThreshold = 400;
    short maxThreshold = 600;

    static void swHandler(Joystick &);
};

#endif
