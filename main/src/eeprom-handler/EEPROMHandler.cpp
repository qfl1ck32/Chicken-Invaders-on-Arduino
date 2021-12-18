#include "./EEPROMHandler.h"

#include "../constants/app.h"

EEPROMHandler::EEPROMHandler(int startAt, int limit) {
    this->startAt = startAt;
    this->limit = limit;

    this->readIndex = startAt;

    for (int i = this->startAt; i < this->limit; ++i) {
        if (EEPROM.read(i) == EEPROM_MISSING_VALUE) {
            this->writeIndex = i;
            break;
        }
    }
}

void EEPROMHandler::resetReadHead() {
    this->readIndex = this->startAt;
}

void EEPROMHandler::writeString(const char* str, int length, int offset = -1) {
    if (this->writeIndex + length > limit) return;

    if (offset == -1) {
        offset = this->writeIndex;
    }

    EEPROM.write(offset, length);

    for (int i = 0; i < length; ++i) EEPROM.write(offset + i + 1, str[i]);

    this->writeIndex += (length + 1);
}

void EEPROMHandler::writeString(const char* str, int length) {
    EEPROMHandler::writeString(str, length, -1);
}

char* EEPROMHandler::readString(int position) {
    int8_t length = EEPROM.read(position);

    char* str = new char[length + 1];

    for (int i = 0; i < length; ++i) str[i] = (char)EEPROM.read(position + 1 + i);

    str[length] = '\0';

    return str;
}

char* EEPROMHandler::readNext() {
    int8_t oldIndex = this->readIndex;

    int length = EEPROM.read(oldIndex);

    if (length == EEPROM_MISSING_VALUE) return 0;

    this->readIndex += length + 1;

    return this->readString(oldIndex);
}

void EEPROMHandler::clear() {
    for (int i = this->startAt; i < this->limit; ++i) EEPROM.write(i, EEPROM_MISSING_VALUE);

    this->writeIndex = this->startAt;
}

int8_t EEPROMHandler::read(int offset) {
    if (offset > this->limit) return 0;

    return EEPROM.read(offset);
}
