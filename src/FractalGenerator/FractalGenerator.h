#ifndef FRACTALGENERATOR_H
#define FRACTALGENERATOR_H

#include "Fractal.h"
#include "Fractals/FractalTypes.h"
#include <iostream>

template <class PreciseFloat>
class FractalGenerator {
public:
    static constexpr unsigned short DEVICE_CPU = 0;
    static constexpr unsigned short DEVICE_CUDA = 1;
    static constexpr unsigned short DEVICE_CPU_CUDA = 2;
    static constexpr unsigned short DEVICE_SHADER = 3;

    static constexpr unsigned short FRACTAL_MANDELBROT = 0;
private:
    unsigned short m_computeDevice = DEVICE_CPU;
    unsigned short m_numCores = 1;

    FractalType<PreciseFloat> *m_algorithm;
public:
    void setComputeDevice(unsigned short deviceFlag) { m_computeDevice = deviceFlag; }
    void setNumCores(unsigned short numCores) { m_numCores = numCores == 0 ? (unsigned short)1 : numCores; }
    void setFractalType(unsigned short fractalType);

    void computeFractal(Fractal<PreciseFloat> &fractal);
    long getLastExecutionTime() { return m_algorithm->getLastExecutionTime(); }

    FractalGenerator();
};


#endif
