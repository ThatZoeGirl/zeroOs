#include <ST7789.h>
#include <ST7789CONF.h>

#include <stdio.h>
#include <stdint.h>
#include <unistd.h>

#include <cstdint>
#include <cmath>

using namespace std;

uint16_t hsv_to_rgb565(float h, float s, float v){
    float r, g, b;
    h = h/360.0f;

    if (s == 0){
        r = g = b = v;
    } else {
        uint8_t i = static_cast<uint8_t>(floor(h * 6.0f));
        float f = h * 6.0f - i;
        float p = v * (1.0f - s);
        float q = v * (1.0f - f * s);
        float t = v * (1.0f - (1.0f - f) * s);

        switch(i % 6){
            case 0: r = v; g = t; b = p; break;
            case 1: r = q; g = v; b = p; break;
            case 2: r = p; g = v; b = t; break;
            case 3: r = p; g = q; b = v; break;
            case 4: r = t; g = p; b = v; break;
            case 5: r = v; g = p; b = q; break;
        }
    }

    uint8_t r5 = static_cast<uint8_t>(r * 255.0f);
    uint8_t g6 = static_cast<uint8_t>(g * 255.0f);
    uint8_t b5 = static_cast<uint8_t>(b * 255.0f);

    r5 = (r5 >> 3) & 0x1F;  // 5 bits for red
    g6 = (g6 >> 2) & 0x3F;  // 6 bits for green
    b5 = (b5 >> 3) & 0x1F;  // 5 bits for blue

    return (r5 << 11) | (g6 << 5) | b5;
}

int main() {
    
    wiringPiSetupGpio();

    initST7789();
    
    uint16_t *buffer = new uint16_t[TFT_WIDTH*TFT_HEIGHT];
    float hue=0.0f;

    for(int i=0; i<0xFFFF; i++){
        if(hue>360.0f){hue=0.0f;};
        for(int y=0; y<TFT_HEIGHT; y++){
            for(int x=0; x<TFT_WIDTH; x++){
                buffer[(y*TFT_WIDTH)+x] = hsv_to_rgb565(hue, ((1.0f/(float)(TFT_WIDTH))*x), 1.0f-((1.0f/(float)(TFT_HEIGHT))*y));
            }
        }
        showBuf(0,0,TFT_WIDTH,TFT_HEIGHT,buffer);
        hue+=1.0f;
    }

    return 0;
}