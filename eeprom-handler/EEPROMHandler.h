#include <EEPROM.h>

class EEPROMHandler {
   public:
    EEPROMHandler(int startAt, int limit) {
        this->startAt = startAt;
        this->limit = limit;
    }

    int startAt;
    int limit;

    String readString(int);

    void writeString(int, const String &);

    void clear();

    byte read(int);
};

void EEPROMHandler::writeString(int offset, const String &str) {
    byte length = str.length();

    EEPROM.write(offset, length);

    for (int i = 0; i < length; ++i) EEPROM.write(offset + i + 1, str[i]);
}

String EEPROMHandler::readString(int position) {
    byte length = EEPROM.read(position);

    String str = "";

    for (int i = 0; i < length; ++i) str.concat((char)EEPROM.read(position + 1 + i));

    return str;
}

void EEPROMHandler::clear() {
    for (int i = 0; i < 1024; ++i) EEPROM.write(i, 255);
}

byte EEPROMHandler::read(int offset) {
    return EEPROM.read(offset);
}
