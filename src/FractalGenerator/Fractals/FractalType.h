#ifndef FRACTALTYPE_H
#define FRACTALTYPE_H

#include "../Fractal.h"

class FractalType {
public:
    virtual void calculate(Fractal &fractal, int numCores, bool cudaEnabled) = 0;

    virtual long getLastExecutionTime() = 0;
};

#endif
