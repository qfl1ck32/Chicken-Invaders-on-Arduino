#include "./Leaderboard.h"

const char *const Leaderboard::nameAndScoreDelimiter = "|";

int Leaderboard::size = 3;

Leaderboard::Leaderboard() {
    this->eeprom = new EEPROMHandler(EEPROM_LEADERBOARD_START_INDEX, 256);

    this->scores = new LinkedList<NameAndScore>();
}

Leaderboard::~Leaderboard() {
    delete this->eeprom;
    delete this->scores;
}

int Leaderboard::getWorstHighscore() {
    if (!this->scores->size) {
        this->generate();
    }

    if (!this->scores->size) return -1;

    int minScore = INT_MAX;

    while (this->scores->size) {
        NameAndScore element = this->scores->removeHead();

        if (element.score < minScore) {
            minScore = element.score;
        }
    }

    return minScore;
}

void Leaderboard::generate() {
    while (this->scores->size) {
        this->scores->removeHead();
    }

    this->eeprom->resetReadHead();

    char *str;

    int currentIndex = 0;

    while ((str = this->eeprom->readNext())) {
        char *pointerToDelimiter = strchr(str, Leaderboard::nameAndScoreDelimiter[0]);

        int delimiterIndex = pointerToDelimiter - str + 1;

        char *name = new char[delimiterIndex];

        strncpy(name, str, delimiterIndex);

        name[delimiterIndex - 1] = '\0';

        short score = atoi(str + delimiterIndex);

        this->scores->add(NameAndScore(name, score));

        free(str);
    }
}

// FIXME: this is not efficient at all, also not dry - but it's less error-prone
void Leaderboard::write(const char *name, int score) {
    uint8_t nameLength = strlen(name);

    char entry[nameLength + getNumberOfDigits(score) + 2];

    strncpy(entry, name, strlen(name));

    strncpy(entry + nameLength, Leaderboard::nameAndScoreDelimiter, 1);

    sprintf(entry + nameLength + 1, "%d", score);

    this->eeprom->writeString(entry, strlen(entry));

    this->generate();

    this->eeprom->clear();

    this->scores->sort(Leaderboard::sort);

    int repeat = min(this->scores->size, Leaderboard::size);

    while (repeat--) {
        NameAndScore nameAndScore = this->scores->removeHead();

        char entry[strlen(nameAndScore.name) + getNumberOfDigits(nameAndScore.score) + 2];

        strncpy(entry, nameAndScore.name, strlen(nameAndScore.name));

        strncpy(entry + strlen(nameAndScore.name), Leaderboard::nameAndScoreDelimiter, 1);

        sprintf(entry + strlen(nameAndScore.name) + 1, "%d", nameAndScore.score);

        this->eeprom->writeString(entry, strlen(entry));
    }
}

bool Leaderboard::isHighScore(int score) {
    int worstHighScore = this->getWorstHighscore();

    if (worstHighScore == -1) return true;

    this->generate();

    return score > worstHighScore || this->scores->size < MAX_HIGHSCORES;
}

int Leaderboard::sort(NameAndScore &a, NameAndScore &b) {
    return a.score < b.score;
}
