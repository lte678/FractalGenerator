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

struct Domain {
    float minX = -2.0f;
    float maxX = 2.0f;
    float minY = -2.0f;
    float maxY = 2.0f;

    Domain() {};
    Domain(float _minX, float _maxX, float _minY, float _maxY) {
        minX = _minX;
        maxX = _maxX;
        minY = _minY;
        maxY = _maxY;
    }
};

class Fractal {
private:
    unsigned short m_height = DEFAULT_FRACTAL_HEIGHT;
    unsigned short m_width = DEfAULT_FRACTAL_WIDTH;
    unsigned int *m_fractal;

    unsigned int m_maxIterations = 100;

    Domain m_domain;
public:
    int getHeight() {return m_height; }
    int getWidth() { return m_width; }

    void setElement(unsigned int elementValue, unsigned short x, unsigned short y);
    float getDomainWidth();
    float getDomainHeight();
    Domain getDomain();
    void setDomain(Domain newDomain);
    void setDomain(float minX, float maxX, float minY, float maxY);

    void setMaxIterations(unsigned int maxIterations) { m_maxIterations = maxIterations; }
    unsigned int getMaxIterations() { return m_maxIterations; }

    unsigned int* getFractal() { return m_fractal; }

    Fractal();
    Fractal(unsigned short width, unsigned short height);
    ~Fractal() { delete m_fractal; }
};


#endif //FRACTALGENERATOR_FRACTAL_H
