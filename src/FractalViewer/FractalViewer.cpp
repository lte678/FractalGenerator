#include <FractalGenerator.h>
#include <Fractal.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <math.h>

const int MODE_ZOOM = 0;
const int MODE_PAN = 1;
int mode = MODE_ZOOM;

bool selecting = false;
bool reupdate = true;

int startPoint[2] = {0};

const int height = 900;
const int width = (int)(height * 1.5f);

const float zoomFactor = 0.8f;
const float minZoomSelection = (float)height / 20.0f;

void convertFractalData(Fractal &fractalData, uint8_t *result) {
    for(int i = 0; i < fractalData.getHeight() * fractalData.getWidth(); i++) {
        uint8_t value = 255 - (uint8_t)fractalData.getFractal()[i] * (255.0f / (float)fractalData.getMaxIterations());
        result[i*4 + 0] = value;
        result[i*4 + 1] = value;
        result[i*4 + 2] = value;
        result[i*4 + 3] = 255;
    }
}

void setModeInd(sf::Text &ind) {
    switch(mode) {
        case MODE_ZOOM:
            ind.setString("Zoom");
            break;
        case MODE_PAN:
            ind.setString("Pan");
            break;
    }
}

sf::Vector2f constrainToRatio(sf::Vector2f vector) {
    float size = vector.x*vector.x + vector.y*vector.y;
    float scaleVal = pow(((float)height / (float)width), 2.0f) + 1.0f;
    size = sqrt(size / scaleVal);
    return sf::Vector2f(size, size * ((float)height / (float)width));
}


float mapFloat(float value, float startIn, float stopIn, float startOut, float endOut) {
    return (value - startIn) * (endOut - startOut) / (stopIn - startIn) + startOut;
}

void setDomain(Fractal &fractal, sf::Vector2f end) {
    sf::Vector2f startReal;
    sf::Vector2f endReal;

    Domain oldDomain = fractal.getDomain();

    startReal.x = mapFloat((float)startPoint[0], 0, width, oldDomain.minX, oldDomain.maxX);
    startReal.y = mapFloat((float)startPoint[1], 0, height, oldDomain.minY, oldDomain.maxY);

    endReal.x = mapFloat(end.x, 0, width, oldDomain.minX, oldDomain.maxX);
    endReal.y = mapFloat(end.y, 0, height, oldDomain.minY, oldDomain.maxY);

    fractal.setDomain(startReal.x, endReal.x, startReal.y, endReal.y);
}

void zoomDomain(Fractal &fractal, float zoom) {
    float oldWidth = fractal.getDomainWidth();
    float oldHeight = fractal.getDomainHeight();

    float widthZoom = (oldWidth * zoom - oldWidth) / 2.0f;
    float heightZoom = (oldHeight * zoom - oldHeight) / 2.0f;

    Domain oldDomain = fractal.getDomain();
    fractal.setDomain(Domain(oldDomain.minX - widthZoom, oldDomain.maxX + widthZoom, oldDomain.minY - heightZoom, oldDomain.maxY + heightZoom));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Demo");
    sf::Texture fractalResult;
    sf::Sprite fractalSurface;
    if(!fractalResult.create(width, height)) {
        std::cerr << "Failed to create pixel array!" << std::endl;
        return EXIT_FAILURE;
    }

    FractalGenerator fractalGen = FractalGenerator();
    Fractal fractal = Fractal(width, height);
    fractal.setDomain(-2.0f, 2.0f, -2.0f * ((float)height / (float)width), 2.0f * ((float)height / (float)width));

    fractalGen.computeFractal(fractal);

    uint8_t *result;
    result = new uint8_t[width * height * 4];
    convertFractalData(fractal, result);
    fractalResult.update(result);
    fractalSurface.setTexture(fractalResult);

    sf::Font font;
    if (!font.loadFromFile("Ubuntu-R.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text processTimeInd("N/A", font, 20);
    processTimeInd.setFillColor(sf::Color::Black);
    processTimeInd.setPosition((float)width - 110.0f, 5.0f);

    sf::Text modeInd("N/A", font, 20);
    modeInd.setFillColor(sf::Color::Black);
    modeInd.setPosition((float)width - 110.0f, 30.0f);
    setModeInd(modeInd);

    sf::RectangleShape selectionBox;
    selectionBox.setFillColor(sf::Color(170, 170, 255, 60));

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyReleased) {
                if(event.key.code == sf::Keyboard::Z) {
                    mode = MODE_ZOOM;
                    setModeInd(modeInd);
                } else if(event.key.code == sf::Keyboard::P) {
                    mode = MODE_PAN;
                    setModeInd(modeInd);
                } else if (event.key.code == sf::Keyboard::Equal) {
                    zoomDomain(fractal, zoomFactor);
                    reupdate = true;
                } else if (event.key.code == sf::Keyboard::Dash) {
                    zoomDomain(fractal, 1.0f / zoomFactor);
                    reupdate = true;
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    startPoint[0] = event.mouseButton.x;
                    startPoint[1] = event.mouseButton.y;
                    if(mode == MODE_ZOOM)
                        selecting = true;
                }
            } else if (event.type == sf::Event::MouseButtonReleased) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    if(selecting) {
                        selecting = false;
                        sf::Vector2f zoomVector = constrainToRatio(sf::Vector2f(sf::Mouse::getPosition(window) - sf::Vector2i(startPoint[0], startPoint[1])));
                        if(zoomVector.x*zoomVector.x + zoomVector.y*zoomVector.y >= minZoomSelection*minZoomSelection) {
                            setDomain(fractal, sf::Vector2f(startPoint[0], startPoint[1]) + zoomVector);
                            reupdate = true;
                        }
                    }
                }
            }

        }

        window.clear();

        if(reupdate) {
            reupdate = false;
            fractalGen.computeFractal(fractal);
            std::ostringstream processTimeText;
            processTimeText << (fractalGen.getLastExecutionTime() / 1000.0f) << "ms";
            processTimeInd.setString(processTimeText.str());

            convertFractalData(fractal, result);
            fractalResult.update(result);
            fractalSurface.setTexture(fractalResult);
        }


        //Drawing code goes here
        window.draw(fractalSurface);
        window.draw(processTimeInd);
        window.draw(modeInd);

        if(selecting) {
            sf::Vector2f tempVec(sf::Mouse::getPosition(window) - sf::Vector2i(startPoint[0], startPoint[1]));
            selectionBox.setSize(constrainToRatio(tempVec));
            selectionBox.setPosition((float)startPoint[0], (float)startPoint[1]);
            window.draw(selectionBox);
        }

        window.display();
    }

    std::cout << "Finished!" << std::endl;

    return 0;
}