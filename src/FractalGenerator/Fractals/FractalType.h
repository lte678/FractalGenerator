#ifndef FRACTALTYPE_H
#define FRACTALTYPE_H

#include "../Fractal.h"

template <class PreciseFloat>
class FractalType {
public:
    virtual void calculate(Fractal<PreciseFloat> &fractal, int numCores, bool cudaEnabled) = 0;

    virtual long getLastExecutionTime() = 0;
};

#endif
