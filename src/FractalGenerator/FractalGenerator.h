#ifndef FRACTALGENERATOR_H
#define FRACTALGENERATOR_H

#include "Fractal.h"
#include "Fractals/FractalTypes.h"

class FractalGenerator {
public:
    static const unsigned short DEVICE_CPU = 0;
    static const unsigned short DEVICE_CUDA = 1;
    static const unsigned short DEVICE_CPU_CUDA = 2;

    static const unsigned short FRACTAL_MANDELBROT = 0;
private:
    unsigned short m_computeDevice = DEVICE_CPU;
    unsigned short m_numCores = 1;

    FractalType *m_algorithm;
public:
    void setComputeDevice(unsigned short deviceFlag) { m_computeDevice = deviceFlag; }
    void setNumCores(unsigned short numCores) { m_numCores = numCores == 0 ? (unsigned short)1 : numCores; }
    void setFractalType(unsigned short fractalType);

    void computeFractal(Fractal &fractal);
    long getLastExecutionTime() { return m_algorithm->getLastExecutionTime(); }

    FractalGenerator();
};


#endif
