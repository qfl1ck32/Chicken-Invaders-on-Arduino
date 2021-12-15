#include "./Leaderboard.h"

const char *const Leaderboard::nameAndScoreDelimiter = "|";

int Leaderboard::size = 3;

int Leaderboard::getWorstHighscore() {
    if (!this->scores->size()) {
        this->generate();
    }

    if (!this->scores->size()) return -1;

    // TODO: a constant? inf?
    int minScore = 2500;

    while (this->scores->size()) {
        NameAndScore element = this->scores->remove(0);

        if (element.score < minScore) {
            minScore = element.score;
        }
    }

    return minScore;
}

void Leaderboard::generate() {
    while (this->scores->size()) {
        this->scores->remove(0);
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

// FIXME: this is not efficient at all, but it's less error-prone
// FIXME: also, not DRY
void Leaderboard::write(const char *name, int score) {
    show("Scriu ", name, ", cu scor ", score);

    char entry[strlen(name) + getNumberOfDigits(score) + 2];

    strncpy(entry, name, strlen(name));

    strncpy(entry + strlen(name), Leaderboard::nameAndScoreDelimiter, 1);

    sprintf(entry + strlen(name) + 1, "%d", score);

    this->eeprom->writeString(entry, strlen(entry));

    this->generate();

    this->eeprom->clear();

    this->scores->sort(Leaderboard::sort);

    Serial.println(this->scores->size());

    int repeat = min(this->scores->size(), 3);

    while (repeat--) {
        NameAndScore nameAndScore = this->scores->remove(0);

        Serial.println("I have a score.");
        Serial.println(nameAndScore.name);
        Serial.println(nameAndScore.score);

        char entry[strlen(nameAndScore.name) + getNumberOfDigits(nameAndScore.score) + 2];

        strncpy(entry, nameAndScore.name, strlen(nameAndScore.name));

        strncpy(entry + strlen(nameAndScore.name), Leaderboard::nameAndScoreDelimiter, 1);

        sprintf(entry + strlen(nameAndScore.name) + 1, "%d", nameAndScore.score);

        this->eeprom->writeString(entry, strlen(entry));
    }
}

bool Leaderboard::isHighScore(int score) {
    int worstHighScore = this->getWorstHighscore();

    Serial.println(worstHighScore);

    if (worstHighScore == -1) return true;

    this->generate();

    Serial.println(score);
    Serial.println(this->scores->size());

    return score > worstHighScore || this->scores->size() < MAX_HIGHSCORES;
}

int Leaderboard::sort(NameAndScore &a, NameAndScore &b) {
    return a.score < b.score;
}
