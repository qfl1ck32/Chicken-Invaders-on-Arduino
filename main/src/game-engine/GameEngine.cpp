#include "./GameEngine.h"

GameEngine::GameEngine(int8_t rows, int8_t columns) {
    this->rows = rows;
    this->columns = columns;

    this->numberOfUnits = 0;

    this->pixelChanges = new LinkedList<PixelChange>();

    this->unitMatrix = new Unit**[rows];

    for (int i = 0; i < rows; ++i) {
        this->unitMatrix[i] = new Unit*[columns];

        for (int j = 0; j < this->columns; ++j) {
            this->unitMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < MAX_UNITS; ++i) {
        this->unitArray[i] = 0;
    }
}

GameEngine::~GameEngine() {
    delete this->pixelChanges;

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            delete this->unitMatrix[i][j];
        }

        delete this->unitMatrix[i];
    }

    delete this->unitMatrix;
}

void GameEngine::resetState() {
    this->numberOfUnits = 0;

    for (int i = 0; i < MAX_UNITS; ++i) {
        if (this->unitArray[i] != 0) {
            delete this->unitArray[i];
        }
    }

    for (int i = 0; i < this->rows; ++i) {
        for (int j = 0; j < this->columns; ++j) {
            this->unitMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < MAX_UNITS; ++i) {
        this->unitArray[i] = 0;
    }
}

void GameEngine::run() {
    for (int i = 0; i < this->numberOfUnits; ++i) {
        this->unitArray[i]->action();
    }

    for (int i = 0; i < this->numberOfUnits; ++i) {
        this->unitArray[i]->react();
    }

    for (int i = 0; i < this->numberOfUnits; ++i) {
        if (this->unitArray[i]->isAlive) {
            continue;
        }

        int x = this->unitArray[i]->x;
        int y = this->unitArray[i]->y;

        this->unitMatrix[x][y] = 0;

        delete this->unitArray[i];

        this->unitArray[i] = 0;

        for (int j = i + 1; j < this->numberOfUnits; ++j) {
            this->unitArray[j - 1] = this->unitArray[j];
        }

        this->pixelChanges->add(PixelChange(x, y, false));

        --this->numberOfUnits;
        --i;
    }
}

bool GameEngine::isValidPosition(int8_t x, int8_t y) {
    return x >= 0 && y >= 0 && x < this->rows && y < this->columns;
}
