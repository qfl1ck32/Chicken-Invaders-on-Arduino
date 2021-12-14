#ifndef GraphicsEngine_h
#define GraphicsEngine_h

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

#endif
