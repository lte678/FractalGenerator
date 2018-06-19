#ifndef MANDELBROTFRACTAL_H
#define MANDELBROTFRACTAL_H

#include "FractalType.h"

template <class PreciseFloat>
class MandelbrotFractal : public FractalType<PreciseFloat> {
private:
    long m_previousExecTime = 0;
public:
    //MandelbrotFractal() : FractalType<PreciseFloat>() {};

    void calculate(Fractal<PreciseFloat> &fractal, int numCores, bool cudaEnabled);

    long getLastExecutionTime() { return m_previousExecTime; }
};


#endif //FRACTALGENERATOR_MANDELBROTFRACTAL_H
