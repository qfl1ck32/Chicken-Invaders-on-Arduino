#ifndef PixelChange_h
#define PixelChange_h

#include "Arduino.h"

class PixelChange {
   public:
    int8_t x, y;
    bool state;

    PixelChange() {}

    PixelChange(int8_t x, int8_t y, bool state) {
        this->x = x;
        this->y = y;

        this->state = state;
    }
};

#endif
