#ifndef Menu_h
#define Menu_h

#include "../app/typedefs.h"
#include "../delayer/Delayer.h"
#include "../lcd/LCD.h"
#include "Arduino.h"

class Menu {
   public:
    LCD *lcd;

    int currentRow;

    const char **messages = nullptr;
    HandlerFunction *handlers = nullptr;

    int numberOfMessages;
    int numberOfHandlers;

    Delayer scrollDelayer = Delayer(200);

    Menu(LCD *lcd) {
        this->lcd = lcd;

        this->numberOfMessages = 0;
        this->numberOfHandlers = 0;

        this->currentRow = 0;
    }

    void setOns(HandlerFunction *, int);

    void setMessages(const char *const *, int);

    void run(bool shouldScrollCurrentRow);

    void run();

    void goUp();

    void goDown();

    void select();
};

#endif
