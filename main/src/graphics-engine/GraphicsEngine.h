#ifndef GraphicsEngine_h
#define GraphicsEngine_h

#include "../matrix/Matrix.h"
#include "../pixel-change/PixelChange.h"

class GraphicsEngine {
   public:
    Matrix *matrix;

    GraphicsEngine(Matrix *&matrix) {
        this->matrix = matrix;
    }

    void renderChanges(PixelChange *, int);
};

#endif
