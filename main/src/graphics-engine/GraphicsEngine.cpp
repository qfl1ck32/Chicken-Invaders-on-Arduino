#include "./GraphicsEngine.h"

void GraphicsEngine::renderChanges(LinkedList<PixelChange> *pixelChanges) {
    while (pixelChanges->size) {
        PixelChange change = pixelChanges->removeHead();

        this->matrix->setLed(0, change.x, change.y, change.state);
    }
}
