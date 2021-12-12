#pragma once

class PixelChange {
   public:
    short x, y;
    bool state;

    PixelChange() {}

    PixelChange(short x, short y, bool state) {
        this->x = x;
        this->y = y;

        this->state = state;
    }
};
