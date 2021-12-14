#include "./Leaderboard.h"

const char *const Leaderboard::nameAndScoreDelimiter = "|";

int Leaderboard::size = 3;

int Leaderboard::getHighscore() {
    LinkedList<NameAndScore> *scores = this->get();
    int maxScore = 0;

    while (scores->size()) {
        NameAndScore element = scores->remove(0);

        if (element.score > maxScore) {
            maxScore = element.score;
        }
    }

    free(scores);

    return maxScore;
}

LinkedList<NameAndScore> *Leaderboard::get() {
    LinkedList<NameAndScore> *leaderboard = new LinkedList<NameAndScore>();

    char *str;

    while ((str = this->eeprom->readNext())) {
        char *pointerToDelimiter = strchr(str, Leaderboard::nameAndScoreDelimiter[0]);

        int delimiterIndex = pointerToDelimiter - str + 1;

        char *name = new char[delimiterIndex];

        strncpy(name, str, delimiterIndex);

        name[delimiterIndex - 1] = '\0';

        short score = atoi(str + delimiterIndex);

        leaderboard->add(NameAndScore(name, score));

        free(str);
    }

    this->eeprom->resetReadHead();

    return leaderboard;
}

void Leaderboard::write(const char *name, int score) {
    char entry[strlen(name) + getNumberOfDigits(score) + 2];

    strncpy(entry, name, strlen(name));

    strncpy(entry + strlen(name), Leaderboard::nameAndScoreDelimiter, 1);

    sprintf(entry + strlen(name) + 1, "%d", score);

    this->eeprom->writeString(entry, strlen(entry));
}