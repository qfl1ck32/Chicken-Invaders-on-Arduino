#include "./NameSelector.h"

#include "../app/globals.h"

NameSelector::~NameSelector() {
    delete[] this->name;
}

NameSelector::NameSelector(LCD *lcd, int row) {
    this->lcd = lcd;
    this->row = row;

    this->name = new char[NAME_MAX_LENGTH + 1];

    for (int i = 0; i < NAME_MAX_LENGTH; ++i) {
        this->name[i] = 0;
    }

    this->name[NAME_MAX_LENGTH] = '\0';

    this->currentLetterIndex = 0;
    this->currentColumn = 0;
}

void NameSelector::goUp() {
    if (!this->isSelected || this->isInvalid) return;

    char currentCharacter = this->name[this->currentColumn];

    if (currentCharacter == ' ') {
        this->name[this->currentColumn] = 'A';
        return;
    }

    this->name[this->currentColumn] = currentCharacter >= 90 ? ' ' : currentCharacter + 1;
}

void NameSelector::goRight() {
    if (this->isSelected || this->isInvalid) return;

    if (this->currentColumn == this->lcd->columns - 1) {
        this->currentColumn = 0;
    }

    else if (this->currentColumn < this->currentLetterIndex) {
        ++this->currentColumn;
    }
}

void NameSelector::goDown() {
    if (!this->isSelected || this->isInvalid) return;

    char currentCharacter = this->name[this->currentColumn];

    if (currentCharacter == ' ') {
        this->name[this->currentColumn] = 'Z';
        return;
    }

    this->name[this->currentColumn] = currentCharacter <= 65 ? ' ' : currentCharacter - 1;
}

void NameSelector::goLeft() {
    if (this->isSelected || this->isInvalid) return;

    if (this->currentColumn == 0) {
        return;
    }

    --this->currentColumn;
}

void NameSelector::select() {
    if (this->isInvalid) return;

    this->isSelected = !this->isSelected;

    if (this->name[this->currentColumn] == 0) {
        this->name[this->currentColumn] = 'A';
    }

    if (this->currentColumn == this->currentLetterIndex && this->currentColumn < NAME_MAX_LENGTH) {
        ++this->currentLetterIndex;
    }
}

// TODO: should first check if the input is not empty?
bool NameSelector::finish() {
    // this->name[this->currentLetterIndex + 1] = '\0';
    return true;
}

void NameSelector::main() {
    static const char msg[] PROGMEM = "Enter your name:";

    char *message = readStringFromPROGMEM(msg);

    this->lcd->printOnRow(message, 0);

    delete message;

    if (this->isSelected) {
        this->lcd->noBlink();
    }

    else {
        this->lcd->blink();
    }

    this->lcd->setCursor(this->currentColumn, this->row);
    this->lcd->printOnRow(this->name, this->row);
}
