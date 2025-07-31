#pragma once
#include <stdio.h>
#include <stdint.h>
#include <cmath>

using namespace std;

// Enums
/**
 * Outline only draws an outline,
 Fill fills everything with secondary color as outline color.
 */
enum filltype {
    OUTLINE,
    FILL
};

/**
 * Determen where to draw a shape.
 */
enum positionalType {
    CENTRE,
    TL,
    TR,
    BL,
    BR
};

// color related functions

/**
 * Turn an r, g and b value into a uint16_t number.
 */
uint16_t rgb(uint8_t r, uint8_t g, uint8_t b);

/**
 * Split a uint16_t number into 2 bytes.
 */
uint8_t* rgb565(uint16_t color);

/**
 * Split a uint16_t number into a seperate r, g and b value.
 */
uint8_t* rgbComp(uint16_t color);

/**
 * Turn hue saturation and value into a uint16_t number.
 */
uint16_t hsv(float hue, float saturation, float value);

// Canvas related classes

/**
 * Base canvas which will serve as base for the frame buffer and sprite.
 */
class Canvas {
    public:
        Canvas(int width, int height);

        int coord(int x, int y);

        void setPixel(int x, int y, uint16_t color);

        void drawLine(int x1, int y1, int x2, int y2, uint16_t color);

        void drawSquare(int x, int y, int width, int height, uint16_t colorPry, uint16_t colorSec, filltype fill, positionalType position);

        void drawCircle(int x, int y, int radius, int borderThickness, uint16_t colorPry, uint16_t colorSec, filltype fill, positionalType position);

        void drawTriangle(int x1, int y1, int x2, int y2, int x3, int y3, int borderThickness, uint16_t colorPry, uint16_t colorSec, filltype fill);

        int width = 0;
        int height = 0;
        uint16_t* buffer;
    private:
        bool isSprite = false;
};

/**
 * FrameBuffer:
 The root canvas. Sum of all sprites will be added onto this canvas in order to get the final image.
 */
class FrameBuffer: public Canvas {
    public:
        using Canvas::Canvas;
        void pushFrame();
    private:
        bool isSprite = false;
};

/**
 * A layer that can be apart of the frame buffer.
 */
class Sprite: public Canvas {
    public:
        Sprite(int width, int height, int zIndex);
        int zIndex = 0;
    private:
        bool isSprite = true;
};