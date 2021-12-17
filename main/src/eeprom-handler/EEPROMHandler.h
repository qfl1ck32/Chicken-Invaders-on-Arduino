#ifndef EEPROMHandler_h
#define EEPROMHandler_h

#include <EEPROM.h>

#include "Arduino.h"

class EEPROMHandler {
   public:
    int startAt, limit, writeIndex, readIndex;

    EEPROMHandler(int, int);

    char* readString(int);

    char* readNext();

    void writeString(const char*, int, int);
    void writeString(const char*, int);

    void resetReadHead();

    void clear();

    int8_t read(int);
};

#endif
