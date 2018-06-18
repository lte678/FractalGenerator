//
// Created by leon on 16.06.18.
//

#include "MandelbrotFractal.h"
#include <iostream>
#include <chrono>

void MandelbrotFractal::calculate(Fractal &fractal, int numCores, bool cudaEnabled) {
    std::cout << "Calculating mandelbrot fractal" << std::endl;

    if(cudaEnabled) {
        std::cerr << "Error: CUDA not implemented for mandelbrot fractal" << std::endl;
        return;
    }

    if(numCores > 1) {
        std::cerr << "Error: Multithreading not implemented for mandelbrot fractal" << std::endl;
        return;
    }

    if(numCores == 0 && !cudaEnabled) {
        std::cerr << "Error: No compute device!" << std::endl;
        return;
    }

    auto startTime = std::chrono::high_resolution_clock::now();

    float rx, ry, wx, wy; //Real x/y and width x/y
    float tmprx;
    float xOffset, yOffset;
    Domain domain = fractal.getDomain();
    xOffset = domain.minX;
    yOffset = domain.minY;
    float origX, origY;

    unsigned int iterations;
    wx = fractal.getDomainWidth() / fractal.getWidth();
    wy = fractal.getDomainHeight() / fractal.getHeight();
    for(unsigned short y = 0; y < fractal.getHeight(); y++) {
        for(unsigned short x = 0; x < fractal.getWidth(); x++) {
            rx = (float)x * wx + 0.5f * wx + xOffset;
            ry = (float)y * wy + 0.5f * wy + yOffset;
            origX = rx;
            origY = ry;
            //std::cout << rx << ", " << ry << std::endl;
            iterations = 0;
            while(rx * rx + ry * ry <= 4.0f && iterations < fractal.getMaxIterations()) {
                tmprx = rx;
                rx = rx * rx - ry * ry;
                ry = 2.0f * tmprx * ry;
                rx += origX;
                ry += origY;
                iterations++;
            }

            fractal.setElement(iterations, x, y);
        }
    }

    auto stopTime = std::chrono::high_resolution_clock::now();
    m_previousExecTime = std::chrono::duration_cast<std::chrono::microseconds>(stopTime-startTime).count();
}