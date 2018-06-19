//
// Created by leon on 16.06.18.
//

#include "FractalTypes.h"

template <class PreciseFloat>
FractalType<PreciseFloat>* FractalTypes::getFractalTypeObject(unsigned short fractalType) {
    switch(fractalType){
        case(FRACTAL_MANDELBROT):
            return new MandelbrotFractal<PreciseFloat>();
        default:
            return new MandelbrotFractal<PreciseFloat>();
    }
};

template FractalType<float>* FractalTypes::getFractalTypeObject<float>(unsigned short fractalType);
template FractalType<double>* FractalTypes::getFractalTypeObject<double>(unsigned short fractalType);
template FractalType<long double>* FractalTypes::getFractalTypeObject<long double>(unsigned short fractalType);