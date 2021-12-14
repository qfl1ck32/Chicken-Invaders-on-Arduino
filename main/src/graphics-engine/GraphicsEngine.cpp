#include "./GraphicsEngine.h"

void GraphicsEngine::renderChanges(PixelChange changes[], int numberOfChanges) {
    for (int i = 0; i < numberOfChanges; ++i) {
        PixelChange change = changes[i];

        this->matrix->setLed(0, change.x, change.y, change.state);
    }
}
