#include "./EEPROMHandler.h"

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
    byte length = EEPROM.read(position);

    char* str = new char[length + 1];

    for (int i = 0; i < length; ++i) str[i] = (char)EEPROM.read(position + 1 + i);

    str[length] = '\0';

    return str;
}

char* EEPROMHandler::readNext() {
    byte oldIndex = this->readIndex;

    byte length = EEPROM.read(this->readIndex);

    if (length == 255) return nullptr;

    this->readIndex += length + 1;

    char* ans = this->readString(oldIndex);

    return ans;
}

void EEPROMHandler::clear() {
    for (int i = 0; i < this->limit; ++i) EEPROM.write(i, 255);

    this->writeIndex = this->startAt;
}

byte EEPROMHandler::read(int offset) {
    if (offset > this->limit) return 0;

    return EEPROM.read(offset);
}
