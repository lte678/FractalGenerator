#include <FractalGenerator.h>
#include <Fractal.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <math.h>

constexpr int MODE_ZOOM = 0;
constexpr int MODE_PAN = 1;
int mode = MODE_ZOOM;

bool selecting = false;
bool dragging = false;
bool reupdate = true;

int startPoint[2] = {0};

const int height = 900;
const int width = (int)(height * 1.5f);

const float zoomFactor = 0.8f;
const float minZoomSelection = (float)height / 20.0f;

typedef double fractalType;

template <class PreciseFloat>
class FractalHelper {
public:
    static void convertFractalData(Fractal<PreciseFloat> &fractalData, uint8_t *result) {
        for(int i = 0; i < fractalData.getHeight() * fractalData.getWidth(); i++) {
            uint8_t value = (uint8_t)(255-((float)fractalData.getFractal()[i] * (255.0f / (float)fractalData.getMaxIterations())));
            result[i*4 + 0] = value;
            result[i*4 + 1] = value;
            result[i*4 + 2] = value;
            result[i*4 + 3] = 255;
        }
    }

    static PreciseFloat mapFloat(PreciseFloat value, PreciseFloat startIn, PreciseFloat stopIn, PreciseFloat startOut, PreciseFloat endOut) {
        return (value - startIn) * (endOut - startOut) / (stopIn - startIn) + startOut;
    }

    static sf::Vector2<PreciseFloat> toFractalCoord(sf::Vector2f displayCoord, Domain<PreciseFloat> &currentDomain) {
        sf::Vector2<PreciseFloat> fractalCoord;
        fractalCoord.x = mapFloat(displayCoord.x, 0, width, currentDomain.minX, currentDomain.maxX);
        fractalCoord.y = mapFloat(displayCoord.y, 0, height, currentDomain.minY, currentDomain.maxY);
        return fractalCoord;
    }

    static void setDomain(Fractal<PreciseFloat> &fractal, sf::Vector2f end) {
        Domain<PreciseFloat> oldDomain = fractal.getDomain();

        sf::Vector2<PreciseFloat> pt1 = toFractalCoord(sf::Vector2f(startPoint[0], startPoint[1]), oldDomain);
        sf::Vector2<PreciseFloat> pt2 = toFractalCoord(end, oldDomain);

        fractal.setDomain(pt1.x, pt2.x, pt1.y, pt2.y);
    }

    static void zoomDomain(Fractal<PreciseFloat> &fractal, float zoom) {
        PreciseFloat oldWidth = fractal.getDomainWidth();
        PreciseFloat oldHeight = fractal.getDomainHeight();

        PreciseFloat widthZoom = (oldWidth * zoom - oldWidth) / 2.0f;
        PreciseFloat heightZoom = (oldHeight * zoom - oldHeight) / 2.0f;

        Domain<PreciseFloat> oldDomain = fractal.getDomain();
        fractal.setDomain(Domain<PreciseFloat>(oldDomain.minX - widthZoom, oldDomain.maxX + widthZoom, oldDomain.minY - heightZoom, oldDomain.maxY + heightZoom));
    }
};


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

int main() {

    sf::RenderWindow window(sf::VideoMode(width, height), "Mandelbrot Demo");
    sf::Texture fractalResult;
    sf::Sprite fractalSurface;
    if(!fractalResult.create(width, height)) {
        std::cerr << "Failed to create pixel array!" << std::endl;
        return EXIT_FAILURE;
    }

    FractalGenerator<fractalType> fractalGen;
    Fractal<fractalType> fractal = Fractal<fractalType>(width, height);
    fractal.setDomain(-2.0f, 2.0f, -2.0f * ((float)height / (float)width), 2.0f * ((float)height / (float)width));

    uint8_t *result;
    result = new uint8_t[width * height * 4];
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
                    FractalHelper<fractalType>::zoomDomain(fractal, zoomFactor);
                    reupdate = true;
                } else if (event.key.code == sf::Keyboard::Dash) {
                    FractalHelper<fractalType>::zoomDomain(fractal, 1.0f / zoomFactor);
                    reupdate = true;
                } else if (event.key.code == sf::Keyboard::R) {
                    reupdate = true;
                }
            } else if (event.type == sf::Event::MouseButtonPressed) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    startPoint[0] = event.mouseButton.x;
                    startPoint[1] = event.mouseButton.y;
                    if(mode == MODE_ZOOM)
                        selecting = true;
                    else if (mode == MODE_PAN)
                        dragging = true;
                }

            } else if (event.type == sf::Event::MouseButtonReleased) {
                if(event.mouseButton.button == sf::Mouse::Left) {
                    if(selecting) {
                        selecting = false;
                        sf::Vector2f zoomVector = constrainToRatio(sf::Vector2f(sf::Mouse::getPosition(window) - sf::Vector2i(startPoint[0], startPoint[1])));
                        if(zoomVector.x*zoomVector.x + zoomVector.y*zoomVector.y >= minZoomSelection*minZoomSelection) {
                            FractalHelper<fractalType>::setDomain(fractal, sf::Vector2f(startPoint[0], startPoint[1]) + zoomVector);
                            reupdate = true;
                        }
                    }
                    if(dragging) {
                        dragging = false;
                        Domain<fractalType> oldDomain = fractal.getDomain();
                        sf::Vector2<fractalType> displacement = FractalHelper<fractalType>::toFractalCoord(sf::Vector2f(startPoint[0], startPoint[1]), oldDomain) - FractalHelper<fractalType>::toFractalCoord(sf::Vector2f(sf::Mouse::getPosition(window)), oldDomain);
                        fractal.setDomain(Domain<fractalType>(oldDomain.minX + displacement.x, oldDomain.maxX + displacement.x, oldDomain.minY + displacement.y, oldDomain.maxY + displacement.y));
                        reupdate = true;
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

            FractalHelper<fractalType>::convertFractalData(fractal, result);
            fractalResult.update(result);
            fractalSurface.setTexture(fractalResult);
            fractalSurface.setPosition(0.0f, 0.0f);
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
        if(dragging) {
            fractalSurface.setPosition(sf::Vector2f(sf::Mouse::getPosition(window)) - sf::Vector2f(startPoint[0], startPoint[1]));
        }

        window.display();
    }

    std::cout << "Finished!" << std::endl;

    return 0;
}