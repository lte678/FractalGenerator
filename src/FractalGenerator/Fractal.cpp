//
// Created by leon on 16.06.18.
//

#include "Fractal.h"


Fractal::Fractal() {
    m_fractal = new unsigned int[m_height * m_width];
    m_domain = Domain();
}

Fractal::Fractal(unsigned short width, unsigned short height) {
    m_width = width;
    m_height = height;
    m_fractal = new unsigned int[m_height * m_width];
    m_domain = Domain();
}

void Fractal::setElement(unsigned int elementValue, unsigned short x, unsigned short y) {
    if(x < m_width && y < m_height) {
        m_fractal[x + y * m_width] = elementValue;
    }
}

float Fractal::getDomainWidth() {
    return m_domain.maxX - m_domain.minX;
}

float Fractal::getDomainHeight() {
    return m_domain.maxY - m_domain.minY;
}

Domain Fractal::getDomain() {
    return m_domain;
}

void Fractal::setDomain(Domain newDomain) {
    m_domain = newDomain;
}

void Fractal::setDomain(float minX, float maxX, float minY, float maxY) {
    m_domain.minX = minX;
    m_domain.maxX = maxX;
    m_domain.minY = minY;
    m_domain.maxY = maxY;
}
