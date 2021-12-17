#ifndef Leaderboard_h
#define Leaderboard_h

#include "../constants/app.h"
#include "../eeprom-handler/EEPROMHandler.h"
#include "../linked-list/LinkedList.h"
#include "../printer/SerialPrinter.h"
#include "../utils/utils.h"
#include "./NameAndScore.h"

#define MAX_HIGHSCORES 3

class Leaderboard {
   public:
    EEPROMHandler *eeprom;

    static const char *const nameAndScoreDelimiter;

    static int size;

    Leaderboard();
    ~Leaderboard();

    LinkedList<NameAndScore> *scores;

    void generate();

    void write(const char *, int);

    int getWorstHighscore();

    bool isHighScore(int);

    static int sort(NameAndScore &, NameAndScore &);
};

#endif
