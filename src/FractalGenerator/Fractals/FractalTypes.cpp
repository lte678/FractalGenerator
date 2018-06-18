//
// Created by leon on 16.06.18.
//

#include "FractalTypes.h"

FractalType* FractalTypes::getFractalTypeObject(unsigned short fractalType) {
    switch(fractalType){
        case(FRACTAL_MANDELBROT):
            return new MandelbrotFractal();
        default:
            return new MandelbrotFractal();
    }
};