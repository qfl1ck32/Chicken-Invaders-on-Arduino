#include "./GameEngine.h"

GameEngine::GameEngine(Matrix *&matrix) {
    this->matrix = matrix;

    this->score = 0;

    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->columns; ++j) {
            this->unitMatrix[i][j] = 0;
        }
    }

    for (int i = 0; i < MAX_UNITS; ++i) {
        this->unitArray[i] = 0;
    }

    this->numberOfUnits = 0;

    this->changes = new LinkedList<PixelChange>();
}

void GameEngine::resetState() {
    this->matrix->clear();

    this->finalScore = this->score;

    this->score = 0;

    this->numberOfUnits = 0;

    // TODO: why
    // for (int i = 0; i < MAX_UNITS; ++i) {
    //     if (this->unitArray[i] != 0) {
    //         delete this->unitArray[i];
    //     }
    // }

    for (int i = 0; i < matrix->rows; ++i) {
        for (int j = 0; j < matrix->columns; ++j) {
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

        this->changes->add(PixelChange(x, y, false));

        --this->numberOfUnits;
        --i;
    }
}

bool GameEngine::isValidPosition(short x, short y) {
    return x >= 0 && y >= 0 && x < this->matrix->rows && y < this->matrix->columns;
}