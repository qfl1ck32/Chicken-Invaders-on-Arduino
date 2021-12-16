#ifndef Matrix_h
#define Matrix_h

#include "../constants/app.h"
#include "EEPROM.h"
#include "LedControl.h"

// FIXME: this class was not thought to be used with more that one matrix
class Matrix : public LedControl {
   public:
    byte rows;
    byte columns;

    byte intensity;

    Matrix(int dataPin, int clkPin, int csPin, int numDevices, byte rows, byte columns) : LedControl(dataPin, clkPin, csPin, numDevices) {
        static byte defaultIntensity = 8;

        this->rows = rows;
        this->columns = columns;

        byte savedIntensity = EEPROM.read(EEPROM_MATRIX_INTENSITY_INDEX);

        this->intensity = savedIntensity == EEPROM_MISSING_VALUE ? defaultIntensity : savedIntensity;

        this->increaseIntensity(0);
    }

    void setup();

    void setLed(int, int, int, boolean);

    void clear();

    void increaseIntensity(short);

    void displayImage(uint64_t);
};

#endif
