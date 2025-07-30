#include <ST7789.h>
#include <ST7789CONF.h>

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include <cstdint>
#include <cmath>

uint16_t hsl_to_rgb565(float h, float s, float l) {
    float c = (1.0f - std::fabs(2.0f * l - 1.0f)) * s;
    float h_prime = h / 60.0f;
    float x = c * (1.0f - std::fabs(fmod(h_prime, 2.0f) - 1.0f));

    float r1 = 0, g1 = 0, b1 = 0;

    if (0 <= h_prime && h_prime < 1) {
        r1 = c; g1 = x; b1 = 0;
    } else if (1 <= h_prime && h_prime < 2) {
        r1 = x; g1 = c; b1 = 0;
    } else if (2 <= h_prime && h_prime < 3) {
        r1 = 0; g1 = c; b1 = x;
    } else if (3 <= h_prime && h_prime < 4) {
        r1 = 0; g1 = x; b1 = c;
    } else if (4 <= h_prime && h_prime < 5) {
        r1 = x; g1 = 0; b1 = c;
    } else if (5 <= h_prime && h_prime < 6) {
        r1 = c; g1 = 0; b1 = x;
    }

    float m = l - c / 2.0f;

    uint8_t r = static_cast<uint8_t>(std::round((r1 + m) * 255));
    uint8_t g = static_cast<uint8_t>(std::round((g1 + m) * 255));
    uint8_t b = static_cast<uint8_t>(std::round((b1 + m) * 255));

    uint16_t r5 = (r >> 3) & 0x1F;  // 5 bits for red
    uint16_t g6 = (g >> 2) & 0x3F;  // 6 bits for green
    uint16_t b5 = (b >> 3) & 0x1F;  // 5 bits for blue

    return (r5 << 11) | (g6 << 5) | b5;
}



int main() {
    
    wiringPiSetupGpio();

    initST7789();
    
    uint16_t *buffer = new uint16_t[TFT_WIDTH*TFT_HEIGHT];
    float hue=0.0f;

    for(int i=0; i<0xFFFF; i++){
        if(hue>360.0f){hue=0;};
        for(int y=0; y<TFT_HEIGHT; y++){
            for(int x=0; x<TFT_WIDTH; x++){
                buffer[(y*TFT_WIDTH)+x] = hsl_to_rgb565(hue, ((1.0f/(float)(TFT_WIDTH))*x), 1.0f-((1.0f/(float)(TFT_HEIGHT))*y));
            }
        }
        showBuf(0,0,TFT_WIDTH,TFT_HEIGHT,buffer);
        hue+=0.5f;
    }

    return 0;
}