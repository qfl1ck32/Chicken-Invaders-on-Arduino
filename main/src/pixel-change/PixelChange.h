#ifndef PixelChange_h
#define PixelChange_h

#include "Arduino.h"

class PixelChange {
   public:
    byte x, y;
    bool state;

    PixelChange() {}

    PixelChange(byte x, byte y, bool state) {
        this->x = x;
        this->y = y;

        this->state = state;
    }
};

#endif
