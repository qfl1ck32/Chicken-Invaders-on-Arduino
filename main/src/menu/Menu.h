#ifndef Menu_h
#define Menu_h

#include <avr/pgmspace.h>

#include "../app/typedefs.h"
#include "../delayer/Delayer.h"
#include "../lcd/LCD.h"
#include "Arduino.h"

class Menu {
   public:
    LCD *lcd;

    int currentRow;

    char **messages = nullptr;
    HandlerFunction *handlers = nullptr;

    int numberOfMessages;
    int numberOfHandlers;

    Delayer scrollDelayer;

    Menu(LCD *);

    void setOns(HandlerFunction *, int);

    void setMessages(char **, int, bool);
    void setMessages(char **, int);

    void run(bool shouldScrollCurrentRow);

    void run();

    void goUp();

    void goDown();

    void select();
};

#endif
