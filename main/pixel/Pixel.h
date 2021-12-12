#pragma once

class Pixel {
   public:
    short x, y;

    Pixel(){};

    Pixel(short x, short y) {
        this->x = x;
        this->y = y;
    }
};
