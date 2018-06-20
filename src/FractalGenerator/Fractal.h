//
// Created by leon on 16.06.18.
//

#ifndef FRACTAL_H
#define FRACTAL_H

#define DEFAULT_FRACTAL_HEIGHT 1024
#define DEfAULT_FRACTAL_WIDTH 1024

#include <malloc.h>

// #include <boost/multiprecision/mpfr.hpp>
//
//How can CUDA handle arbitrary length floats? => Stick with CUDA supported types for now
//
//namespace mp = boost::multiprecision;
//typedef

template <class PreciseFloat>
struct Domain {
    PreciseFloat minX = -2.0f;
    PreciseFloat maxX = 2.0f;
    PreciseFloat minY = -2.0f;
    PreciseFloat maxY = 2.0f;

    Domain() {};
    Domain(PreciseFloat _minX, PreciseFloat _maxX, PreciseFloat _minY, PreciseFloat _maxY) {
        minX = _minX;
        maxX = _maxX;
        minY = _minY;
        maxY = _maxY;
    }
};

template <class PreciseFloat>
class Fractal {
private:
    unsigned short m_height = DEFAULT_FRACTAL_HEIGHT;
    unsigned short m_width = DEfAULT_FRACTAL_WIDTH;
    unsigned int *m_fractal;

    unsigned int m_maxIterations = 2500;

    Domain<PreciseFloat> m_domain;
public:
    int getHeight() {return m_height; }
    int getWidth() { return m_width; }

    void setElement(unsigned int elementValue, unsigned short x, unsigned short y);
    PreciseFloat getDomainWidth();
    PreciseFloat getDomainHeight();
    Domain<PreciseFloat> getDomain();
    void setDomain(Domain<PreciseFloat> newDomain);
    void setDomain(PreciseFloat minX, PreciseFloat maxX, PreciseFloat minY, PreciseFloat maxY);

    void setMaxIterations(unsigned int maxIterations) { m_maxIterations = maxIterations; }
    unsigned int getMaxIterations() { return m_maxIterations; }

    unsigned int* getFractal() { return m_fractal; }

    Fractal();
    Fractal(unsigned short width, unsigned short height);
    ~Fractal() { delete m_fractal; }
};


#endif //FRACTALGENERATOR_FRACTAL_H
