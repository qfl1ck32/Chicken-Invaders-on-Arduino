#include "./GraphicsEngine.h"

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

        this->matrix->setLed(0, change.x, change.y, change.state);
    }
}
