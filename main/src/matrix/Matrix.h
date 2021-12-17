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

    Matrix(int dataPin, int clkPin, int csPin, int numDevices, int8_t rows, int8_t columns) : LedControl(dataPin, clkPin, csPin, numDevices) {
        static int8_t defaultIntensity = 8;

        this->rows = rows;
        this->columns = columns;

        int8_t savedIntensity = EEPROM.read(EEPROM_MATRIX_INTENSITY_INDEX);

        this->intensity = savedIntensity == EEPROM_MISSING_VALUE ? defaultIntensity : savedIntensity;

        this->increaseIntensity(0);
    }

    void setup();

    void setLed(int, int, int, boolean);

    void setAllLeds(bool);

    void increaseIntensity(short);

    void displayImage(uint64_t);
};

#endif
