//
// Created by leon on 16.06.18.
//

#include "FractalGenerator.h"

FractalGenerator::FractalGenerator() {
    m_algorithm = FractalTypes::getFractalTypeObject(0);
}

void FractalGenerator::computeFractal(Fractal &fractal) {
    if(m_computeDevice == DEVICE_CPU) {
        m_algorithm->calculate(fractal, m_numCores, false);
    } else if(m_computeDevice == DEVICE_CPU_CUDA) {
        m_algorithm->calculate(fractal, m_numCores, true);
    } else if(m_computeDevice == DEVICE_CUDA) {
        m_algorithm->calculate(fractal, 0, true);
    }
}

void FractalGenerator::setFractalType(unsigned short fractalType) {
    delete m_algorithm;
    m_algorithm = FractalTypes::getFractalTypeObject(fractalType);
}