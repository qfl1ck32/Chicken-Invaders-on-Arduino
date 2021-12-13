#pragma once

class NameSelector {
   public:
    LCD *lcd;

    short currentColumn;

    int row;

    bool isSelected = false;

    bool isInvalid = false;

    Delayer errorDelayer = Delayer(2000);

    char *name;

    short currentLetterIndex;

    NameSelector(LCD *lcd, int row) {
        this->lcd = lcd;
        this->row = row;

        this->name = new char[this->lcd->columns];

        for (int i = 0; i < this->lcd->columns; ++i) {
            this->name[i] = 0;
        }

        this->currentLetterIndex = 0;
        this->currentColumn = 0;
    }

    void goUp();
    void goRight();
    void goDown();
    void goLeft();

    void select();

    bool finish();

    void handleInvalidFinish();

    void main();
};

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

    if (this->currentColumn == this->currentLetterIndex) {
        ++this->currentLetterIndex;
    }
}

bool NameSelector::finish() {
    // TODO: handle the case when it's not 0, but it only got spaces
    // if (this->name.length() == 0) {
    //     this->handleInvalidFinish();
    //     return false;
    // }

    return true;
}

void NameSelector::handleInvalidFinish() {
    if (this->errorDelayer.canRun()) {
        // this->lcd->printOnRow("Invalid name.", 1);
    }
}

void NameSelector::main() {
    static const char *const msg PROGMEM = "Enter your name:";

    this->lcd->printOnRow(msg, 0);

    this->isInvalid = false;

    if (this->isSelected) {
        this->lcd->noBlink();
    }

    else {
        this->lcd->blink();
    }

    this->lcd->setCursor(this->currentColumn, this->row);
    this->lcd->printOnRow(this->name, this->row);
}