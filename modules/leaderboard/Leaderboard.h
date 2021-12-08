#pragma once

#include "../../eeprom-handler/EEPROMHandler.h"

class Leaderboard {
   public:
    EEPROMHandler* eeprom;

    int currentPosition;

    static String nameAndScoreDelimiter;
    static String entryDelimiter;

    static int size;

    Leaderboard() {
        this->eeprom = new EEPROMHandler(0, 256);

        this->eeprom->clear();

        if (this->eeprom->read(0) != 255) {
            int i = 1;

            while (this->eeprom->read(i) && i < 256) {
                ++i;
            }

            this->currentPosition = i;
        }

        else {
            this->currentPosition = 0;
        }
    }

    char** get();

    void write(String, float);
};

String Leaderboard::nameAndScoreDelimiter = "|";
String Leaderboard::entryDelimiter = ";";
int Leaderboard::size = 10;

char** Leaderboard::get() {
    // LinkedList<String> *leaderboard = new LinkedList<String>();

    // int position = 0;

    // while (this->eeprom->read(position) != 255 && position < this->eeprom->limit) {
    //     String str = this->eeprom->readString(position);

    //     int delimiterIndex = str.indexOf(Leaderboard::nameAndScoreDelimiter);

    //     String name = str.substring(0, delimiterIndex);

    //     String score = str.substring(delimiterIndex + 1);

    //     String entry = name;

    //     entry.concat(" | ");

    //     entry.concat(score);

    //     leaderboard->add(entry);

    //     position += str.length();
    // }

    // return leaderboard;
}

void Leaderboard::write(String name, float score) {
    String entry = name;

    entry.concat(Leaderboard::nameAndScoreDelimiter);
    entry.concat(score);

    this->eeprom->writeString(this->currentPosition, entry);

    this->currentPosition += entry.length();
}
