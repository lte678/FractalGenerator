#ifndef FRACTALTYPES_H
#define FRACTALTYPES_H

#include "FractalType.h"
#include "MandelbrotFractal.h"

namespace FractalTypes {
    const unsigned short FRACTAL_MANDELBROT = 0;

    FractalType* getFractalTypeObject(unsigned short fractalType);
}

#endif
