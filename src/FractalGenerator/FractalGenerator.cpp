//
// Created by leon on 16.06.18.
//

#include "FractalGenerator.h"

template <class PreciseFloat>
FractalGenerator<PreciseFloat>::FractalGenerator() {
    m_algorithm = FractalTypes::getFractalTypeObject<PreciseFloat>(0);
}

template <class PreciseFloat>
void FractalGenerator<PreciseFloat>::computeFractal(Fractal<PreciseFloat> &fractal) {
    if(m_computeDevice == DEVICE_CPU) {
        m_algorithm->calculate(fractal, m_numCores, false);
    } else if(m_computeDevice == DEVICE_CPU_CUDA) {
        m_algorithm->calculate(fractal, m_numCores, true);
    } else if(m_computeDevice == DEVICE_CUDA) {
        m_algorithm->calculate(fractal, 0, true);
    } else {
        std::cerr << "Not implemented!" << std::endl;
    }
}

template <class PreciseFloat>
void FractalGenerator<PreciseFloat>::setFractalType(unsigned short fractalType) {
    delete m_algorithm;
    m_algorithm = FractalTypes::getFractalTypeObject<PreciseFloat>(fractalType);
}


template class FractalGenerator<long double>;
template class FractalGenerator<double>;
template class FractalGenerator<float>;
