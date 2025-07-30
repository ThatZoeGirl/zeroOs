#include <zGfx.h>
#include <cmath>
#include <stdio.h>

using namespace std;

uint16_t rgb(uint8_t r, uint8_t g, uint8_t b){
    r = (r >> 3) & 0x1F;  // 5 bits for red
    g = (g >> 2) & 0x3F;  // 6 bits for green
    b = (b >> 3) & 0x1F;  // 5 bits for blue
    return (r << 11) | (g << 5) | b;
};

uint8_t* rgb565(uint16_t color){
    uint8_t* duo;
    duo[0] = color >> 8;
    duo[1] = color & 0xFF;
    return duo;
};

uint8_t* rgbComp(uint16_t color){
    float r = ((color >> 11) & 0x1F)/31.0f;
    float g = ((color >> 5) & 0x3F)/63.0f;
    float b = (color & 0x1F)/31.0f;

    uint8_t* triplet;
    triplet[0] = floor(r*255.0f);
    triplet[1] = floor(g*255.0f);
    triplet[2] = floor(b*255.0f);

    return triplet;
};

uint16_t hsv(float hue, float saturation, float value){
    float r, g, b;
    hue = hue/360.0f;

    if (saturation == 0){
        r = g = b = value;
    } else {
        uint8_t i = static_cast<uint8_t>(floor(hue * 6.0f));
        float f = hue * 6.0f - i;
        float p = value * (1.0f - saturation);
        float q = value * (1.0f - f * saturation);
        float t = value * (1.0f - (1.0f - f) * saturation);

        switch(i % 6){
            case 0: r = value; g = t; b = p; break;
            case 1: r = q; g = value; b = p; break;
            case 2: r = p; g = value; b = t; break;
            case 3: r = p; g = q; b = value; break;
            case 4: r = t; g = p; b = value; break;
            case 5: r = value; g = p; b = q; break;
        }
    }
    uint8_t r8 = floor(r * 255.0f);
    uint8_t g8 = floor(g * 255.0f);
    uint8_t b8 = floor(b * 255.0f);

    return rgb(r8, g8, b8);
};