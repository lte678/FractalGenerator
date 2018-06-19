//
// Created by leon on 16.06.18.
//

#include "Fractal.h"


template <class PreciseFloat>
Fractal<PreciseFloat>::Fractal() {
    m_fractal = new unsigned int[m_height * m_width];
    m_domain = Domain<PreciseFloat>();
}

template <class PreciseFloat>
Fractal<PreciseFloat>::Fractal(unsigned short width, unsigned short height) {
    m_width = width;
    m_height = height;
    m_fractal = new unsigned int[m_height * m_width];
    m_domain = Domain<PreciseFloat>();
}

template <class PreciseFloat>
void Fractal<PreciseFloat>::setElement(unsigned int elementValue, unsigned short x, unsigned short y) {
    if(x < m_width && y < m_height) {
        m_fractal[x + y * m_width] = elementValue;
    }
}

template <class PreciseFloat>
PreciseFloat Fractal<PreciseFloat>::getDomainWidth() {
    return m_domain.maxX - m_domain.minX;
}

template <class PreciseFloat>
PreciseFloat Fractal<PreciseFloat>::getDomainHeight() {
    return m_domain.maxY - m_domain.minY;
}

template <class PreciseFloat>
Domain<PreciseFloat> Fractal<PreciseFloat>::getDomain() {
    return m_domain;
}

template <class PreciseFloat>
void Fractal<PreciseFloat>::setDomain(Domain<PreciseFloat> newDomain) {
    m_domain = newDomain;
}

template<class PreciseFloat>
void Fractal<PreciseFloat>::setDomain(PreciseFloat minX, PreciseFloat maxX, PreciseFloat minY, PreciseFloat maxY) {
    m_domain.minX = minX;
    m_domain.maxX = maxX;
    m_domain.minY = minY;
    m_domain.maxY = maxY;
}


template class Fractal<float>;
template class Fractal<double>;
template class Fractal<long double>;