#pragma once

#include <LinkedList.h>

#include "../matrix/Matrix.h"
#include "../pixel-change/PixelChange.h"

class GraphicsEngine {
   public:
    Matrix *matrix;

    bool **state;

    GraphicsEngine(Matrix *&matrix) {
        this->matrix = matrix;
        this->state = NULL;
    }

    void render();

    void renderChanges(LinkedList<PixelChange> *);
};

void GraphicsEngine::render() {
    for (int row = 0; row < matrix->rows; ++row) {
        for (int col = 0; col < matrix->columns; ++col) {
            this->matrix->setLed(0, row, col, this->state[row][col]);
        }
    }
}

void GraphicsEngine::renderChanges(LinkedList<PixelChange> *changes) {
    while (changes->size()) {
        PixelChange change = changes->remove(0);

        // show(change.x, ", ", change.y, ", ", change.state);

        this->matrix->setLed(0, change.x, change.y, change.state);
    }
}
