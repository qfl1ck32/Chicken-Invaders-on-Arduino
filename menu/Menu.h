#pragma once

#include "../delayer/Delayer.h"

class Menu {
   public:
    LCD *lcd;

    int currentRow = 0;

    const char **messages = nullptr;
    HandlerFunction *handlers = nullptr;

    int numberOfMessages;
    int numberOfHandlers;

    Delayer scrollDelayer = Delayer(400);

    Menu(LCD *lcd) {
        this->lcd = lcd;

        this->numberOfMessages = 0;
        this->numberOfHandlers = 0;
    }

    void setHandlers(HandlerFunction *, int);

    void setMessages(const char **, int);

    void run(bool shouldScrollCurrentRow);

    void goUp();

    void goDown();

    void select();
};

void Menu::setMessages(const char **messages, int numberOfMessages) {
    // if (this->messages != nullptr) {
    //     for (int i = 0; i < this->numberOfMessages; ++i) {
    //         free(this->messages[i]);
    //     }

    //     free(this->messages);
    // }

    // FIXME: this->messages = messages; ?
    this->messages = new const char *[numberOfMessages];

    for (int i = 0; i < numberOfMessages; ++i) {
        this->messages[i] = messages[i];
    }

    this->numberOfMessages = numberOfMessages;
}

void Menu::setHandlers(HandlerFunction handlers[], int numberOfHandlers) {
    if (this->handlers != nullptr) {
        free(this->handlers);
    }

    this->handlers = new HandlerFunction[numberOfHandlers];

    for (int i = 0; i < numberOfHandlers; ++i) {
        this->handlers[i] = handlers[i];
    }

    this->numberOfHandlers = numberOfHandlers;
}

void Menu::run(bool shouldScrollCurrentRow = false) {
    int i = this->currentRow >= this->lcd->rows ? this->currentRow - this->lcd->rows + 1 : 0;

    int row = 0;

    while (row < this->lcd->rows) {
        const char *currentMessage = (row == this->currentRow - i ? "> " : "  ");

        char result[strlen(currentMessage) + strlen(this->messages[i + row]) + 1];

        strncpy(result, currentMessage, strlen(currentMessage) + 1);

        strcat(result, this->messages[i + row]);

        this->lcd->printOnRow(result, row);

        if (shouldScrollCurrentRow && row && row == this->currentRow - i && this->scrollDelayer.canRun()) {
            this->lcd->scrollRow(row, 2);
        }

        row++;
    }
}

void Menu::goUp() {
    this->currentRow = this->currentRow == 0 ? this->numberOfMessages - 1 : this->currentRow - 1;
}

void Menu::goDown() {
    this->currentRow = this->currentRow == this->numberOfMessages - 1 ? 0 : this->currentRow + 1;
}

void Menu::select() {
    if (this->currentRow < this->numberOfHandlers && this->handlers[this->currentRow]) this->handlers[this->currentRow]();
}
