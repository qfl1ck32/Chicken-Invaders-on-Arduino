#include <EEPROM.h>

class EEPROMHandler {
   public:
    short startAt, limit, writeIndex, readIndex;

    EEPROMHandler(int startAt, int limit) {
        this->startAt = startAt;
        this->limit = limit;

        this->readIndex = startAt;

        for (int i = 0; i < 1024; ++i) {
            if (EEPROM.read(i) == 255) {
                this->writeIndex = i;
                break;
            }
        }
    }

    char* readString(int);

    char* readNext();

    void writeString(const char*, int, int);

    void resetReadHead();

    void clear();

    byte read(int);
};

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
}

byte EEPROMHandler::read(int offset) {
    if (offset > this->limit) return 0;

    return EEPROM.read(offset);
}
