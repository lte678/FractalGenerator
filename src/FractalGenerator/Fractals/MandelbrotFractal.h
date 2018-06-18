#ifndef MANDELBROTFRACTAL_H
#define MANDELBROTFRACTAL_H

#include "FractalType.h"

class MandelbrotFractal : public FractalType {
private:
    long m_previousExecTime = 0;
public:
    MandelbrotFractal() {};

    void calculate(Fractal &fractal, int numCores, bool cudaEnabled);

    long getLastExecutionTime() { return m_previousExecTime; }
};


#endif //FRACTALGENERATOR_MANDELBROTFRACTAL_H
