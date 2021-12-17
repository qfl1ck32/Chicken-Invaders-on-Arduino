#ifndef Matrix_h
#define Matrix_h

#include "../constants/app.h"
#include "EEPROM.h"
#include "LedControl.h"

// FIXME: this class was not thought to be used with more that one matrix
class Matrix : public LedControl {
   public:
    int8_t rows;
    int8_t columns;

    int8_t intensity;

    Matrix(int, int, int, int, int8_t, int8_t);

    void setup();

    void setLed(int, int, int, boolean);

    void setAllLeds(bool);

    void increaseIntensity(short);

    void displayImage(uint64_t);
};

#endif
