#ifndef Joystick_h
#define Joystick_h

#include "../app/typedefs.h"
#include "Arduino.h"

class Joystick {
   public:
    byte pinSw;
    short pinX;
    short pinY;

    Joystick(byte pinSw, short pinX, short pinY) {
        this->pinSw = pinSw;
        this->pinX = pinX;
        this->pinY = pinY;

        this->handlerXAxisChangeLeft = nullptr;
        this->handlerXAxisChangeRight = nullptr;

        this->handlerYAxisChangeUp = nullptr;
        this->handlerYAxisChangeDown = nullptr;
    }

    bool swState = false;

    void setup(void (*swHandler)());

    void handleJoystickMovements();
    void clearHandlers();

    void clearHandlerSwStateChange();

    void setHandlerOnXAxisChangeLeft(HandlerFunction);
    void setHandlerOnXAxisChangeRight(HandlerFunction);

    void setHandlerOnYAxisChangeUp(HandlerFunction);
    void setHandlerOnYAxisChangeDown(HandlerFunction);

    void setHandlerSwStateChange(HandlerFunction);

    void handleJoystickMovementOnAxisY();
    void handleJoystickMovementOnAxisX();

    void handleSw();

    void (*handlerXAxisChangeLeft)();
    void (*handlerXAxisChangeRight)();

    void (*handlerYAxisChangeUp)();
    void (*handlerYAxisChangeDown)();

    void (*handlerSwStateChange)();

    bool joyMovedOnXAxis = false;
    bool joyMovedOnYAxis = false;

    int minThreshold = 400;
    int maxThreshold = 600;

    static void swHandler(Joystick *);
};

#endif
