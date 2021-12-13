#pragma once

class Pixel {
   public:
    byte x, y;

    Pixel(){};

    Pixel(byte x, byte y) {
        this->x = x;
        this->y = y;
    }
};
